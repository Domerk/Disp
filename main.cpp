//================================= main.cpp =================================

#include <QtGui>
#include "mwgt.h"

int main (int argc, char **argv)
{
    QApplication app (argc, argv);

    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    Mwgt w; //создаём окошко
    w.show(); //показываем окошко
    return app.exec();
}
//==============================================================================
