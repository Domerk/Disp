//================================ wqueue.h ====================================

#ifndef WQUEUE_H
#define WQUEUE_H

#include <QtGui>
#include <QVector>

//==================================================
//============== класс - окно очереди ==============
//==================================================

class Wqueue : public QWidget
{
    Q_OBJECT //Этот макрос указывает компилятору moc, что нужно внедрить в
    //файл дополнительную информацию, прежде чем передать его
    //стандартному компилятору С++

public:
    Wqueue(QWidget *parent = 0);
    ~Wqueue();
    virtual void paintEvent(QPaintEvent *);

private:
   QPainter* painter;
   QPalette pal;
   QVector <int> xproces;
   QVector <QColor> colors;
   int hr, wr, wheight, wwidth;

public slots:
   void SlotQueue(int nStep, QColor nColor);

};

#endif // WQUEUE_H
//==============================================================================
