#include "mainwindow.h"
#include <QApplication>
#include <QtGui>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    MainWindow w;
    w.show();

    return a.exec();
}

/*
Описание грамматики:
S -> F;
F -> if E then T else F 1 | if E then F 2 | a := a 3
T -> if E then T else T 4 | a := a 5
E -> a < a 6  | a > a 7 | a = a 8

Символ S является начальным символом грамматики; S, F, T и E обозначают нетерминальные символы.
Терминальные символы выделены жирным шрифтом.
Вместо терминального символа a подставляются лексемы: идентификаторы или римские числа.
*/
