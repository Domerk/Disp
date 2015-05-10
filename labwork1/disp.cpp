//================================= disp.cpp =================================

#include "disp.h"


Disp::Disp(QWidget *parent) : QWidget(parent)
{
    painter = new QPainter(); //художник
    setFixedSize(900,500); // задаём размеры окошка

    // задаём цвет окошка
    pal.setColor(this->backgroundRole(), Qt::white);
    this->setPalette(pal);
    this->setAutoFillBackground(true);

    nt = 0; // номер такта - 0
    ActivPrID = -1; // активных процессов нет
    STEP = 3; // шаг - 3
    a = 2; // переменная из формулы - 2
    vsize = 0; // зармер вектора процессов - 0

}

//==================================================
//==================================================

void Disp::paintEvent(QPaintEvent* event)
{
    painter->begin(this); //начинаем рисовать в окне

    // рисуем 2 серые горизонтальные линиии
    painter->setPen(QPen(Qt::darkGray,2));
    painter->drawLine(0, 90, 900, 90);
    painter->drawLine(0, 360, 900, 360);

    // рисуем 3 чёрные горизонтальные линиии
    painter->setPen(QPen(Qt::black,2));
    painter->drawLine(0, 170, 900, 170);
    painter->drawLine(0, 240, 900, 240);
    painter->drawLine(0, 310, 900, 310);

    // настраиваем рисование текста
    int x = 50;
    int y = 70;
    painter->setPen(QPen(Qt::black,1));
    painter->setFont(QFont("Arial", 10, QFont::Normal));

    // рисуем шкалу времени на чёрных линиях
    for (int j = 1; j<4; j++)
    {
        x = 50;
        for (int i = 0; i<17; i++)
        {
            painter->drawLine(x, 90+y*j, x, 90+y*j+20);
            painter->drawText(x-2, 90+y*j+40, QString(tr("%1")).arg(i+1+17*(j-1)));
            x+=50;
        }
    }

    // рисуем надписис
    painter->drawText(10, 20, tr("Процесс"));
    painter->drawText(10, 45, tr("Длительность"));
    painter->drawText(10, 70, tr("Приоритет"));
    painter->drawText(10, 120, tr("Выполнение"));
    painter->drawText(10, 390, tr("Очередь"));

    char pname = 'A';

    for (int i=1; i<=10; i++)
    {
        painter->drawText(70+70*i, 20, QString(pname));
        pname++;
    }

    painter->drawText(840, 20, tr("Такт"));
    QRect r = QRect(835, 35, 40, 40);
    painter->drawRect(r);
    painter->setFont(QFont("Arial", 12, QFont::Normal));
    painter->drawText(r, Qt::AlignCenter, QString(tr("%1")).arg(nt));

    // если процессы существуют, отправляем им художника
    // чтобы они могли себя нарисовать
    for (int i = 0; i<vsize; i++)
    {
        VProc.at(i)->show(painter);
    }

    painter->end();//освобождаем окно
}

//==================================================
//==================================================

void Disp::timerEvent(QTimerEvent *event)
{

    nt++; // увеличиваем значение текущего такта
    emit signalTime(nt); // сообщаем об этом процессам

    if (nt%STEP == 0) // если номер такта без остатка делится на шаг
    {
        ChangePriority(); // изменяем приоритеты
    }

    PrActivate(); // активируем процессы
    repaint(); // перерисовываем содержимое окошка
}

//==================================================
//==================================================

void Disp::ChangePriority()
{
    int npr; // новый приоритет

    for (int i = 0; i<vsize; i++) // для всех существующих процессов
    {
        // если процесс находится в состоянии готовности
        if (VProc.at(i)->reportAPriority() != -1 && i!=ActivPrID)
        {
            // Формула Pri=Pr0i+ai*t*t
            npr = VProc.at(i)->reportNPriority()+ a *(VProc.at(i)->reportPrTmAct())*(VProc.at(i)->reportPrTmAct());
            VProc.at(i)->changePriority(npr);
        }
    }

}

//==================================================
//==================================================

void Disp::PrActivate()
{
    bool nexist = Pr.empty(); // существует ли очереди?
    // если очререди нет и нет выполняющихся процессов
    if (nexist && ActivPrID == -1)
    {
        return; // то выходим
    }

    int pmax = -1;
    int ipmax = -1;
    int sz = Pr.size();

    for (int i = 0; i<sz; i++) // для всей очереди
    {
        if (pmax < VProc.at(Pr.at(i))->reportAPriority())
        {
            // находим процесс с максимальным приоритетом
            // и сохраняем его положение и приоритет
            pmax = VProc.at(Pr.at(i))->reportAPriority();
            ipmax = Pr.at(i);
        }
    }

    // если какой-то процесс выполняется и очередь не пуста
    if (ipmax != -1 && ActivPrID != -1)
    {
        if (ipmax != ActivPrID) // если макимальный приоритет не у выполняемого процесса
        {
            VProc.at(ActivPrID)->disactivate(); // дезактивируем

            int del = 0;

            for (int s = 0; s<sz; s++) // ищем его в очереди
            {
                if (ActivPrID != Pr.at(del))
                {
                    del++;
                }
            }
            Pr.erase(Pr.begin()+del); // удаляем

            Pr.push_back(ActivPrID); // и добавляем в конец
            ActivPrID = ipmax; // сохраняем id выполняемого процесса
            VProc.at(ActivPrID)->activate(); // запускаем процесс

        }
        else // иначе если текущий процесс не кончился
        {
            if (VProc.at(ActivPrID)->reportNPriority()>-1)
            {
                VProc.at(ActivPrID)->activate(); // пусть работает
            }
        }
    }

    // если нет активных процессов, а очередь не пуста
    if (pmax != -1 && ActivPrID == -1)
    {
        // активируем процесс с максимальным приоритетом
        VProc.at(ipmax)->activate();
        ActivPrID = ipmax;

    }

    // для всех процессов из очереди
    for (int i = 0; i<sz; i++)
    {
        // находим из в контейнере процессов
        for (int j = 0; j<vsize; j++)
        {
            if (j == Pr.at(i))
            {
                // сообщаем место в очереди
                VProc.at(j)->setQueuePos(i);

                // и если процесс в состоянии готовности
                if (j != ActivPrID)
                {
                    // посылаем сигнал для рисования очереди
                    emit signalQueue(nt, VProc.at(j)->reportMyColor());
                }
            }
        }
    }
}

//==================================================
//==================================================

void Disp::slotDO (QVector <int> Vct)
{

    // здесь будем создавать процессы с символьными именами
    // каждое следующее имя ++
    // передаём в конструктор процесса его имя и два последующих элемента из Vct
    // если доительность равна 0, то не создаём процесс

    char pname='A';
    int n = 0;

    for (int i = 0; i<19; i+=2)
    {
        if (Vct.at(i))
        {
            VProc.append(new Proces(pname, Vct.at(i), Vct.at(i+1), n));
            n++;
        }
        pname++;
    }


    vsize = VProc.size();

    for (int i = 0; i<vsize; i++)
    {
        connect(this, SIGNAL(signalTime(int)), VProc.at(i), SLOT(slotTime(int)));
        connect(VProc.at(i), SIGNAL(IMReady(int)), this, SLOT(PrReady(int)));
        connect(VProc.at(i), SIGNAL(IFinished(int)), this, SLOT(PrFinished(int)));
    }

    emit signalTime(nt);
    ChangePriority(); // вычисляем приоритеты
    startTimer(1500); // запускаем таймер

}

//==================================================
//==================================================

void Disp::PrReady(int PrID)
{
    // процессу, перешедшему в состояние готовности
    // задаём 0й приоритет
    VProc.at(PrID)->setPriority(0);
    // добавляем его в конец очереди
    Pr.push_back(PrID);

    if (ActivPrID == -1) // если активных процессов нет, то разрешаем выполнится
    {
        VProc.at(PrID)->activate();
        ActivPrID=PrID;
    }
    else
    {
        // иначе сообщаем процессу его место в очереди
        int n = Pr.size();
        for (int i = 0; i<n; i++)
        {
            if (Pr.at(i) == PrID)
            {
                VProc.at(PrID)->setQueuePos(i);
            }
        }
    }
}

//==================================================
//==================================================

void Disp::PrFinished(int PrID)
{

    // если процесс выполнился и очередь существует
    if (!Pr.empty())
    {
        // Ищем его в очереди и удаляем
        int del = 0;
        while (PrID != Pr.at(del))
        {
            del++;
        }
        Pr.erase(Pr.begin()+del);
    }
    // устанавливаем id активного процесса в -1
    ActivPrID = -1;
}

//==================================================
//==================================================

void Disp::slotOS (int os)
{
    STEP = os; // устаналиваем новое значение шага
}

//==================================================
//==================================================

Disp::~Disp()
{
    delete painter;
}
//==============================================================================
