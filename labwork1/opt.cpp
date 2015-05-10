//================================= opt.cpp =================================

#include "opt.h"

const int M_Dur = 8; // максимальные значения времени
const int M_In = 10;


Options::Options(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(300,380); // фиксированный размер
    setWindowTitle(tr("Создание процессов"));

    vb = new QVBoxLayout(); // вертикальная компановка
    vb->setSpacing(20); // параметр растяжения

    gl1 = new QGridLayout(); // табличная компановка
    gl1->setVerticalSpacing(10); // параметр растяжения

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

    // заполняем вектор спинбоксов
    // устанавливаем соотвествующие ограничения
    for (int i=0; i<19; i+=2)
    {
        Vt.append(new QSpinBox());
        Vt.append(new QSpinBox());
        Vt[i]->setMaximum(M_Dur);
        Vt[i+1]->setMaximum(M_In);
        Vt[i+1]->setMinimum(1);
    }

    int j = 1;
    int i = 0;

    // добавляем спинбоксы в компановку
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


    //================== Кнопочки ==================

    hb = new QHBoxLayout; // горизонтальная компановка
    pb1 = new QPushButton (tr("Старт")); // кнопка "Старт"
    hb->addWidget(pb1); // добавляем её в компановку
    connect(pb1, SIGNAL(clicked()), SLOT(DO())); // соеднияем сигнал "нажатие кнопки" и нужный слот

    pb2 = new QPushButton (tr("Сброс")); // кнопка "Сброс настроек"
    hb->addWidget(pb2);
    connect(pb2, SIGNAL(clicked()), SLOT(STOP()));
    vb->addLayout(hb);

    this->setLayout(vb);
}

//==================================================
//==================================================
void Options::DO()
{
    // передаём значения при помощи вектора
    for (int i = 0; i<20; i++)
    {
        Vct.append(Vt[i]->value());
    }

    pb1->setEnabled(false); // делаем кнопку неактивной
    // то есть пока не сделан сброс
    // создание новых процессов невозможно
    emit sendDO(Vct); // передаём вектор времени */
}


//==================================================
//==================================================
void Options::STOP()
{
    // делаем кнопку создания доступной
    pb1->setEnabled(true);
    // очищаем вектор настроек
    Vct.clear();
    emit SSTOP(); // посылаем сигнал сброса
}


//==================================================
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
