#include "webcapture.h"
//#include "thumbnailer.h"

#include <QApplication>
#include <iostream>


int main(int argc, char * argv[])
{

    if (argc < 3) {
        std::cout << "not enough parameters: webcapture url img [width height]" << std::endl;
        return 0;
    }

    QUrl url = QUrl::fromUserInput(QString::fromLatin1(argv[1]));
    QString fileName = QString::fromLatin1(argv[2]);

    QSize size = QSize(384,100);

    if (argc == 5) {
    	size.setWidth(QString::fromLatin1(argv[3]).toInt());
        size.setHeight(QString::fromLatin1(argv[4]).toInt());
    }
    
    QApplication a(argc, argv); // QApplication::Tty

    WebCapture capture(size);
    QObject::connect(&capture, SIGNAL(finished()), QApplication::instance(), SLOT(quit()));
    
    capture.load(url, fileName);
    return a.exec();
}

