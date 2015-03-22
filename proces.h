#ifndef PROCES_H
#define PROCES_H

#include <QtGui>
#include <ctime>
#include <QVector>

class Proces : public QObject // ��������� QObject
{
    Q_OBJECT // ������, ����������� ��� ������ � ��������� � �������

private:
    char PrName; // ��� ��������
    int PrTmDur; // ������������
    int PrTmAct; // ����� ����������
    int TActDur; // ������� ������ ��� ����� �����������
    bool PrActive;
    int px, py;

public:
    Proces(char NName, int NDur, int NAct);
    ~Proces();
    void show(QPainter *painter); // ���������

};
#endif // PROCES_H
