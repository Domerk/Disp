#ifndef PROCES_H
#define PROCES_H

#include <QtGui>
#include <ctime>
#include <QVector>

class Proces : public QObject // наследует QObject
{
    Q_OBJECT // макрос, необходимый для работы с сигналами и слотами

private:
    char PrName; // имя процесса
    int PrTmDur; // длительность
    int PrTmAct; // время готовности
    int TActDur; // сколько тактов ещё будет выполняться
    bool PrActive;
    int px, py;

public:
    Proces(char NName, int NDur, int NAct);
    ~Proces();
    void show(QPainter *painter); // рисовалка

};
#endif // PROCES_H
