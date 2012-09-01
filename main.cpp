#include "webcapture.h"
//#include "thumbnailer.h"

#include <QApplication>
#include <iostream>


int main(int argc, char * argv[])
{


    if (argc < 2) {
        std::cout << "not enough parameters: webcapture url [img] [width height]" << std::endl;
        return 0;
    }

    QUrl url = QUrl::fromUserInput(QString::fromLatin1(argv[1]));

    bool direct = false;
    QString fileName = "";

    if (argc == 3) {
    	fileName = QString::fromLatin1(argv[2]);
    } else {
	direct = true;
    }

    QSize size = QSize(384,100);

    std::cout << "Filename: " << qPrintable(fileName) << std::endl;

    if (argc == 5) {
    	size.setWidth(QString::fromLatin1(argv[3]).toInt());
        size.setHeight(QString::fromLatin1(argv[4]).toInt());
    }
    
    QApplication a(argc, argv); // QApplication::Tty

    WebCapture capture(size, direct);
    QObject::connect(&capture, SIGNAL(finished()), QApplication::instance(), SLOT(quit()));
    
    capture.load(url, fileName);
    return a.exec();
}

