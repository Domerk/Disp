//================================= wgt2.h =================================

#ifndef WGT2
#define WGT2

#include <QtWidgets>
#include "sim.h"

class Wgt : public QWidget
{
    Q_OBJECT

private:
    QMap <char, QProgressBar*> pbMap;
    QMap <char, QLabel*> labelMap;
    QMap <char, QHBoxLayout*> hblMap;
    QGraphicsPixmapItem * processImage;
    QLabel * table;
    QGraphicsScene *scene;
    QGraphicsView * view;
    QLabel *processLabel;
    QVBoxLayout *vLayout;
    QHBoxLayout *mainLayout;
    QPalette pal;
    QPushButton *button1;
    QPushButton *button2;
    QPushButton *button3;
    QLabel *lbl;
    QHBoxLayout *hLayout;
    QTextEdit *textEdit;
    QFile logFile;
    QThread simThread;

public:
    explicit Wgt(QWidget *parent = 0);
    ~Wgt();
    Sim *sim;
private slots:
    void setProgress(char, int);
    void start();
    void log();
    void restart();

public slots:
    void prFinished();
};

#endif // WGT2
//==============================================================================

