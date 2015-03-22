//================================ mwgt.h ====================================

#ifndef MWGT_H
#define MWGT_H

#include <QtGui>
#include <QLabel>
#include <QMenuBar>
#include <QVector>

#include "disp.h"
#include "opt.h"

//==================================================
//============ класс - окно приложения =============
//==================================================

class Mwgt : public QMainWindow //Наследует базовый класс библиотеки Qt
{
    Q_OBJECT //Этот макрос указывает компилятору moc, что нужно внедрить в
    //файл дополнительную информацию, прежде чем передать его
    //стандартному компилятору С++
public:
    Mwgt(QMainWindow *parent = 0); // конструктор
    ~Mwgt(); // деструктор
private slots:
    virtual void label_program(); // слоты
    virtual void label_developer();
    virtual void label_help();
    virtual void options();

private:
    QMenuBar* menuBar; // меню
    QMenu* pmenu;
    QMenu* pmenu1;
    QMenu* pmenu2;
    QMenu* pmenu3;
    QLabel* lprogram; // надписи
    QLabel* ldeveloper;
    QLabel* lhelp;
    QHBoxLayout* mainLayout; // компановка
    QWidget* mainWidget; // дополнительный виджет

    Disp* disp;
    Options* opt;

};



#endif // MWGT_H
