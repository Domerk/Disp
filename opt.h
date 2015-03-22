#ifndef OPT_H
#define OPT_H

#include <QtGui>
#include <QVector>

class Options : public QWidget
{
    Q_OBJECT
private:
    QVBoxLayout* vb; //  вертикальная компановка
    QGridLayout* gl1; // табличная компановка

    QHBoxLayout* hb; // горизонтальная компановка

    QLabel* lP1; // надписи
    QLabel* lP2;
    QLabel* lP3;
    QLabel* lP4;
    QLabel* lP5; // ещё надписи
    QLabel* lP6;
    QLabel* lP7;
    QLabel* lP8;
    QLabel* lP9;
    QLabel* lP10;

    QLabel* lPr;
    QLabel* lDur;
    QLabel* lIn;

    QVector <QSpinBox*> Vt;

    QPushButton* pb1; // кнопки
    QPushButton* pb2;
public:
    Options(QWidget *parent = 0); // конструктор
    ~Options(); // деструктор
signals:
   void sendDO (QVector <int> vct); // сигнал
private slots:
   virtual void DO(); // слоты
   virtual void RESTART();
};

#endif // OPT_H
