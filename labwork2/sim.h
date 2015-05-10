//================================= sim.h =================================

#ifndef SIM_H
#define SIM_H

#include <QtWidgets>

class Sim : public QObject
{
    Q_OBJECT
public:
    explicit Sim(QObject *parent = 0);
    ~Sim();
    const int n {100};
    int **M;
    bool *R;
    QMap<char, bool> runMap;
    QFile logFile;
    QMutex mMutex, rMutex, rmMutex, fileMutex;

    /* Мьютексы — это простейшие двоичные семафоры, которые могут находиться
       в одном из двух состояний — отмеченном или неотмеченном (открыт и закрыт соответственно).
       Когда какой-либо поток, принадлежащий любому процессу, становится владельцем объекта mutex,
       последний переводится в неотмеченное состояние. Если задача освобождает мьютекс,
       его состояние становится отмеченным.
      */

signals:
    void progressChanged(char, int);
    void finished();

public slots:
    void start();
    void a();
    void b();
    void c(char parent);
    void d(char parent);
    void e(char parent);
    void f(char parent);
    void g(char parent);
    void h(char parent);
    void i(char parent);
    void log(QString);
    void init();
};

#endif // SIM_H
//==============================================================================
