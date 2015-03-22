#include "disp.h"

Disp::Disp(QWidget *parent) : QWidget(parent)
{
    painter = new QPainter(); //художник
    setFixedSize(450,450);

    startTimer(10);

}

void Disp::paintEvent(QPaintEvent* event)
{
    painter->begin(this); //начинаем рисовать в окне
 //   painter->drawImage(0,0,QImage("://images/crossroad.jpg"));

     painter->end();//освобождаем окно
}

void Disp::timerEvent(QTimerEvent *event)
{
    repaint();
}


void Disp::slotDO (QVector <int> vct)
{
    OVt = vct; // принимаем вектор времени
  //  emit signalTT(times); // передаём его
}


Disp::~Disp()
{
delete painter;
}
