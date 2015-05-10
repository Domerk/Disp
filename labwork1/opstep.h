//================================ opstep.h ====================================

#ifndef OPSTEP_H
#define OPSTEP_H

#include <QtGui>
#include <QVector>

//==================================================
//============== класс - окно настроек =============
//==================================================

class OpStep : public QWidget
{
    Q_OBJECT //Этот макрос указывает компилятору moc, что нужно внедрить в
    //файл дополнительную информацию, прежде чем передать его
    //стандартному компилятору С++

private:
    QVBoxLayout* vb; // компановка
    QLabel* lTxt; // надпись
    QSpinBox* SBt; // спинбокс
    QPushButton* pb; // кнопочка

public:
    OpStep(QWidget *parent = 0); // конструктор
    ~OpStep(); // деструктор

signals:
    void signalOS (int); // сигнал

private slots:
    virtual void slotOS();

};

#endif // OPSTEP_H
//==============================================================================
