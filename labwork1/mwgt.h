//================================ mwgt.h ====================================

#ifndef MWGT_H
#define MWGT_H

#include <QtGui>
#include <QLabel>
#include <QMenuBar>
#include <QVector>

#include "disp.h"
#include "opt.h"
#include "opstep.h"
#include "wqueue.h"

//==================================================
//============ класс - окно приложения =============
//==================================================

class Mwgt : public QMainWindow //Наследует класс главного окна Qt
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
    virtual void opsteps();
    virtual void opwqueue();

public slots:
    void slotSTOP();

private:
    QMenuBar* menuBar; // меню
    QMenu* pmenu; // пункты меню
    QMenu* pmenu1;
    QMenu* pmenu2;
    QMenu* pmenu3;
    QLabel* lprogram; // надписи
    QLabel* ldeveloper;
    QLabel* lhelp;
    QHBoxLayout* mainLayout; // компановка
    QWidget* mainWidget; // дополнительный виджет
    QPalette pal;

    Disp* disp; // Дисптечер
    Options* opt; // Окно создания процессов
    OpStep* ost; // Окно настроек
    Wqueue* wque; // График очереди
    QScrollArea* qsa; // Окно с полосой прокрутки

};

#endif // MWGT_H
//==============================================================================
