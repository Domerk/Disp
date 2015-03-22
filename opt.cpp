#include "opt.h"

const int M_Dur = 10; // максимальные значения времени
const int M_In = 10;


Options::Options(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(300,380); // фиксированный размер
    vb = new QVBoxLayout(); // вертикальная компановка

    vb->setSpacing(20);


    gl1 = new QGridLayout();

    gl1->setVerticalSpacing(10);

    lPr = new QLabel(tr("<center><H4>Процесс</H4></center>"));
    lDur = new QLabel(tr("<center><H4>Длительность</H4></center>"));
    lIn = new QLabel(tr("<center><H4>Начало</H4></center>"));


    lP1 = new QLabel(tr("<center>А:</center>"));
    lP2 = new QLabel(tr("<center>B:</center>"));
    lP3 = new QLabel(tr("<center>C:</center>"));
    lP4 = new QLabel(tr("<center>D:</center>"));
    lP5 = new QLabel(tr("<center>E:</center>"));
    lP6 = new QLabel(tr("<center>F:</center>"));
    lP7 = new QLabel(tr("<center>G:</center>"));
    lP8 = new QLabel(tr("<center>H:</center>"));
    lP9 = new QLabel(tr("<center>I:</center>"));
    lP10 = new QLabel(tr("<center>J:</center>"));


   // QVector <QSpinBox*> Vt(20);

    for (int i=0; i<19; i+=2)
    {
        Vt[i] = new QSpinBox();
        Vt[i]->setMaximum(M_Dur);
        Vt[i+1] = new QSpinBox();
        Vt[i+1]->setMaximum(M_In);
    }


    int j = 1;
    int i = 0;

    while(i<19 && j<=10)
    {
      gl1->addWidget(Vt[i], j, 1);
      gl1->addWidget(Vt[i+1], j, 2);
      j++;
      i+=2;
    }

    gl1->addWidget(lPr, 0, 0);
    gl1->addWidget(lDur, 0, 1);
    gl1->addWidget(lIn, 0, 2);

    gl1->addWidget(lP1, 1, 0);
    gl1->addWidget(lP2, 2, 0);
    gl1->addWidget(lP3, 3, 0);
    gl1->addWidget(lP4, 4, 0);
    gl1->addWidget(lP5, 5, 0);
    gl1->addWidget(lP6, 6, 0);
    gl1->addWidget(lP7, 7, 0);
    gl1->addWidget(lP8, 8, 0);
    gl1->addWidget(lP9, 9, 0);
    gl1->addWidget(lP10, 10, 0);


    vb->addLayout(gl1);

    this->setLayout(vb);


    //================== Buttons ==================
    hb = new QHBoxLayout; // горизонтальная компановка
    pb1 = new QPushButton (tr("Применить")); // кнопка "Применить"
    hb->addWidget(pb1); // добавляем её в компановку
    connect(pb1, SIGNAL(clicked()), SLOT(DO())); // соеднияем сигнал "нажатие кнопки" и нужный слот
    pb2 = new QPushButton (tr("Сброс")); // кнопка "Сброс настроек"
    hb->addWidget(pb2);
    connect(pb2, SIGNAL(clicked()), SLOT(RESTART()));
    vb->addLayout(hb);
    this->setLayout(vb);
}


//==================================================
//======= слот, принимающий значения настроек ======
//==================================================

void Options::DO()
{
    QVector <int> vct(20);

    for (int i = 0; i<20; i++)
    {
        Vt[0];
        //vct[i] = Vt[i]->value();
    }

    emit sendDO(vct); // передаём вектор времени
}


//==================================================
//========== слот, сбрасывающий настройки ==========
//==================================================
void Options::RESTART()
{
  //  emit RESTART();
}


//==================================================
//==================== деструктор ==================
//==================================================
Options::~Options()
{
    delete vb;
    delete gl1;
    delete hb;

    delete lP1;
    delete lP2;
    delete lP3;
    delete lP4;
    delete lP5;
    delete lP6;
    delete lP7;
    delete lP8;
    delete lP9;
    delete lP10;

    delete lPr;
    delete lDur;
    delete lIn;

    delete pb1;
    delete pb2;
}
//==============================================================================
