#ifndef OPT_H
#define OPT_H

#include <QtGui>
#include <QVector>

class Options : public QWidget
{
    Q_OBJECT
private:
    QVBoxLayout* vb; //  ������������ ����������
    QGridLayout* gl1; // ��������� ����������

    QHBoxLayout* hb; // �������������� ����������

    QLabel* lP1; // �������
    QLabel* lP2;
    QLabel* lP3;
    QLabel* lP4;
    QLabel* lP5; // ��� �������
    QLabel* lP6;
    QLabel* lP7;
    QLabel* lP8;
    QLabel* lP9;
    QLabel* lP10;

    QLabel* lPr;
    QLabel* lDur;
    QLabel* lIn;

    QVector <QSpinBox*> Vt;

    QPushButton* pb1; // ������
    QPushButton* pb2;
public:
    Options(QWidget *parent = 0); // �����������
    ~Options(); // ����������
signals:
   void sendDO (QVector <int> vct); // ������
private slots:
   virtual void DO(); // �����
   virtual void RESTART();
};

#endif // OPT_H
