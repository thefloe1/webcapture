#include "webcapture.h"

#include <iostream>
#include <QWebPage>
#include <QWebFrame>
#include <QWebElement>
#include <QPainter>
#include <QImage>
#include <QByteArray>
#include <QBuffer>

/* based on a example found in qt library */


WebCapture::WebCapture(const QSize &viewport, bool direct): QObject()
{
    this->viewport = viewport;
    this->direct = direct;

    m_page.mainFrame()->setScrollBarPolicy(Qt::Vertical, Qt::ScrollBarAlwaysOff);
    m_page.mainFrame()->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAlwaysOff);
    m_page.setViewportSize(viewport);
    connect(&m_page, SIGNAL(loadFinished(bool)), this, SLOT(saveResult(bool)));
}

void WebCapture::load(const QUrl &url, const QString &outputFileName)
{

    m_fileName = outputFileName;
    m_page.mainFrame()->load(url);

}

void WebCapture::saveResult(bool ok)
{
    // crude error-checking
    if (!ok || m_page.bytesReceived()<1) {
        std::cerr << "Failed loading " << qPrintable(m_page.mainFrame()->url().toString()) << std::endl;
        emit finished();
        return;
    }

    saveFrame(m_page.mainFrame());

    emit finished();
}

void WebCapture::saveFrame(QWebFrame *frame)
{
    QString fileName(m_fileName);

    int frameHeight = frame->contentsSize().height();
    //std::cout << "Web Height:" << frameHeight << std::endl;

    if (frameHeight > viewport.height())
        viewport.setHeight(frameHeight);

    QImage image(viewport, QImage::Format_RGB32);
    image.fill(Qt::white);

    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    frame->documentElement().render(&painter);

    painter.end();

    /*
    QByteArray img_data = QByteArray((const char *) image.bits(), image.byteCount());

    */

    if (direct) {
	QByteArray ba;
	QBuffer buf(&ba);
	image.save(&buf, "PNG");

	std::cout << ba.toBase64().data() << std::endl;
	return;
    } else {
    
    	image.save(fileName);
	std::cout << "Save file: "<<qPrintable(fileName)<<std::endl;
    }
}

