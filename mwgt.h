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
//============ ����� - ���� ���������� =============
//==================================================

class Mwgt : public QMainWindow //��������� ������� ����� ���������� Qt
{
    Q_OBJECT //���� ������ ��������� ����������� moc, ��� ����� �������� �
    //���� �������������� ����������, ������ ��� �������� ���
    //������������ ����������� �++
public:
    Mwgt(QMainWindow *parent = 0); // �����������
    ~Mwgt(); // ����������
private slots:
    virtual void label_program(); // �����
    virtual void label_developer();
    virtual void label_help();
    virtual void options();

private:
    QMenuBar* menuBar; // ����
    QMenu* pmenu;
    QMenu* pmenu1;
    QMenu* pmenu2;
    QMenu* pmenu3;
    QLabel* lprogram; // �������
    QLabel* ldeveloper;
    QLabel* lhelp;
    QHBoxLayout* mainLayout; // ����������
    QWidget* mainWidget; // �������������� ������

    Disp* disp;
    Options* opt;

};



#endif // MWGT_H
