
#include <QtGui>
#include "mwgt.h"

int main (int argc, char **argv)
{
    QApplication app (argc, argv);

    QTextCodec::setCodecForTr(QTextCodec::codecForName("System"));

    Mwgt w; //������ ������
    w.show(); //���������� ������
    return app.exec();
}
