//================================= main.cpp =================================

#include <QtGui>
#include <QApplication>
#include "mwgt.h"

int main (int argc, char **argv)
{
    // Кодировка UTF-8
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QResource::registerResource("images.qrc"); // Файл ресурсов

    QApplication app (argc, argv);

    QTranslator myTranslator;
    myTranslator.load("bb-" + QLocale::system().name());
    app.installTranslator(&myTranslator);

    Mwgt w; //создаём окошко
    w.show(); //показываем окошко
    return app.exec();
}
//==============================================================================
