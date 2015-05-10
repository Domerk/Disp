//================================ disp.h ====================================

#ifndef DISP_H
#define DISP_H

#include <QtGui>
#include <QVector>
#include <ctime>
#include "proces.h"

//==================================================
//============ класс - диспетчер задач =============
//==================================================

class Disp : public QWidget
{
    Q_OBJECT //Этот макрос указывает компилятору moc, что нужно внедрить в
    //файл дополнительную информацию, прежде чем передать его
    //стандартному компилятору С++

public:
    Disp(QWidget *parent = 0);
    ~Disp(); 
    virtual void paintEvent(QPaintEvent *);

protected:
    virtual void timerEvent(QTimerEvent *); //отвечает за время

private:
    QPainter* painter; //"художник" 
    QVector <Proces*> VProc; // вектор процессов
    QVector <int> Pr; // вектор очереди
    QPalette pal; // палитра
    int a;
    int nt;
    int ActivPrID; // номер активного процесса
    int STEP; // шаг пересчёта
    int vsize; // размер вектора процессов

    void ChangePriority(); // пересчёт приоритетов
    void PrActivate(); // активация процессов

public slots: // слоты
    void slotDO (QVector <int> Vct); // слот для создания процессов
    void PrReady(int PrID); // слот - готовность процесса
    void PrFinished(int PrID); // слот - завершение процесса
    void slotOS (int os); // слот для изменения шага пересчёта

signals:
    void signalTime(int nt); // сигнал - время
    void signalQueue(int nt, QColor color); // сигнал - такт и цвет процесса
};

#endif // DISP_H
//==============================================================================
