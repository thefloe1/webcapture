#ifndef WEBCAPTURE_H
#define WEBCAPTURE_H

#include <QWebPage>
#include <QSize>

class WebCapture : public QObject
{
    Q_OBJECT

public:
    WebCapture(const QSize &size, bool direct=false);
    void load(const QUrl &url, const QString &outputFileName);

signals:
    void finished();

private slots:
    void saveResult(bool ok);

private:
    QWebPage m_page;
    QString m_fileName;

    QSize viewport;
    void saveFrame(QWebFrame *frame);

    bool direct;
};

#endif
