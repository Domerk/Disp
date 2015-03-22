#ifndef DISP_H
#define DISP_H

#include <QtGui>
#include <QVector>
#include <ctime>

class Disp : public QWidget
{
    Q_OBJECT

public:
    Disp(QWidget *parent = 0);
    ~Disp();
    virtual void paintEvent(QPaintEvent *);

protected:
    virtual void timerEvent(QTimerEvent *); //�������� �� �����
private:
    QPainter* painter; //"��������"
    QVector <int> OVt;

public slots:
    void slotDO (QVector <int> vct); // �����
};

#endif // DISP_H
