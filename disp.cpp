#include "disp.h"

Disp::Disp(QWidget *parent) : QWidget(parent)
{
    painter = new QPainter(); //��������
    setFixedSize(450,450);

    startTimer(10);

}

void Disp::paintEvent(QPaintEvent* event)
{
    painter->begin(this); //�������� �������� � ����
 //   painter->drawImage(0,0,QImage("://images/crossroad.jpg"));

     painter->end();//����������� ����
}

void Disp::timerEvent(QTimerEvent *event)
{
    repaint();
}


void Disp::slotDO (QVector <int> vct)
{
    OVt = vct; // ��������� ������ �������
  //  emit signalTT(times); // ������� ���
}


Disp::~Disp()
{
delete painter;
}
