//================================= mwgt.h =================================

#ifndef MWGT_H
#define MWGT_H

#include <QtGui>
#include <QMainWindow>
#include <QLabel>
#include <QMenuBar>
#include <QVector>

#include "wgt2.h"

class Mwgt : public QMainWindow
{
    Q_OBJECT

public:
    Mwgt(QMainWindow *parent = 0); // конструктор
    ~Mwgt(); // деструктор

private slots:
    virtual void label_program(); // слоты
    virtual void label_developer();
    virtual void label_help();

private:
    QMenuBar* menuBar; // меню
    QMenu* pmenu; // пункты меню
    QMenu* pmenu1;
    QMenu* pmenu2;
    QMenu* pmenu3;
    QLabel* lprogram; // надписи
    QLabel* ldeveloper;
    QLabel* lhelp;
    Wgt* wgt;
    QVBoxLayout *mainLayout;

};

#endif // MWGT_H
//==============================================================================
