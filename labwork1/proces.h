//================================ proces.h ====================================

#ifndef PROCES_H
#define PROCES_H

#include <QtGui>
#include <ctime>
#include <QVector>
#include <QColor>

//==================================================
//=============== класс - процесс ==================
//==================================================

class Proces : public QObject // наследует QObject
{
    Q_OBJECT //Этот макрос указывает компилятору moc, что нужно внедрить в
    //файл дополнительную информацию, прежде чем передать его
    //стандартному компилятору С++

private:

    // атрибуты, необходимые для симулации действий процесса

    char PrName; // имя процесса
    int PrTmDur; // длительность
    int PrTmAct; // время готовности
    int TActDur; // сколько тактов ещё будет выполняться
    int PrID; // id процесса
    bool PrActive; // флаг активности процесса
    int Step; // номер текущего такта

    // атрибуты, необходимые для анимации
    // на самом деле процесс может не хранить эту информацию

    int xtext; // положение текста
    int queuePos; // положение в очереди
    int tq; // количество тактов, которое процесс провёл в очереди
    QVector <int> XVt; // вектор коодинат
    QColor MyColor; // цвет
    int pr; // приоритет - начальный
    int apr; // приоритет - текущий


public:
    Proces(char NName, int NDur, int NAct, int nID); // конструктор
    void show(QPainter *painter); // рисовалка
    void setPriority(int nPriority); // установить приоритет
    void changePriority(int nPriority); // изменить приоритет
    int reportNPriority(); // сообщить начальный приоритет
    int reportAPriority(); // сообщить текущий приоритет
    int reportPrTmAct(); // сообщить время стояния в очереди
    QColor reportMyColor(); // сообщить цвет
    void activate(); // активироваться - перейти к выполнению
    void disactivate(); // декативироваться - перейти к готовности
    void setQueuePos(int qp); // установить плорядок в очереди
    ~Proces(); // деструктор

public slots:
    void slotTime (int nStep); // слот для времени

signals:
    void IMReady(int PrID); // сигнал о переходе в состояние готовности
    void IFinished(int PrID); // сигнал о заверщении работы

};
#endif // PROCES_H
//==============================================================================
