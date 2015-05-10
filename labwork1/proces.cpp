//================================= proces.cpp =================================

#include "proces.h"

Proces::Proces(char NName, int NDur, int NAct, int nID)
{

    PrName = NName; // имя
    PrTmDur = NDur; // длительность
    PrTmAct = NAct; // через сколько будет готов
    TActDur = NDur; // сколько будет выполняться - изначально равно длительности
    PrActive = false; // активность - не активен
    PrID = nID; // id
    pr = -1; // начальный приоритет -1
    apr = -1; // актуальный приоритет -1
    queuePos = -1; // места в очереди нет
    tq = 0; // в очереди не стоял

    switch (PrName) // устанавливаем для процесса цвет - он зависит от имени
    {
    case 'A':
        MyColor=Qt::yellow;
        xtext = 140;
        break;
    case 'B':
        MyColor=Qt::darkRed;
        xtext = 210;
        break;
    case 'C':
        MyColor=Qt::magenta;
        xtext = 280;
        break;
    case 'D':
        MyColor=Qt::darkMagenta;
        xtext = 350;
        break;
    case 'E':
        MyColor=Qt::blue;
        xtext = 420;
        break;
    case 'F':
        MyColor=Qt::darkBlue;
        xtext = 490;
        break;
    case 'G':
        MyColor=Qt::cyan;
        xtext = 560;
        break;
    case 'H':
        MyColor=Qt::darkCyan;
        xtext = 630;
        break;
    case 'I':
        MyColor=Qt::green;
        xtext = 700;
        break;
    case 'J':
        MyColor=Qt::darkGreen;
        xtext = 770;
        break;
    }
}

//==================================================
//==================================================

void Proces::show(QPainter *painter)
{
    // рисуем цветной кружочек возле соотвествующей буквы
    painter->setPen(QPen(MyColor));
    painter->setBrush(QBrush(MyColor));
    painter->drawEllipse(xtext+15, 10, 10, 10);

    // узнаём размер вектора координат и рисуем для каждой координаты
    // цветной прямоугольничек. При этом учитываем значение координаты
    // и при необходимости переходим на другую линеечку
    int n = XVt.size();

    for (int i = 0; i<n; i++)
    {
        if (XVt.at(i)<900)
        {
            painter->drawRect(XVt.at(i), 148, 50, 20);
        }
        else
        {
            if (XVt.at(i)<1750)
            {
                painter->drawRect(XVt.at(i)-850, 218, 50, 20);
            }
            else
            {
                painter->drawRect(XVt.at(i)-1700, 288, 50, 20);
            }
        }
    }

    // рисуем очередь, координата калратика зависист от места в очереди
    if (queuePos > 0 && TActDur > 0)
    {
        painter->drawRect(10+(queuePos-1)*50, 400, 50, 50);
    }

    // выводим инфу о приоритете и оставшейся длительности
    // инфа о приоритете начинает выводится, когда процесс готов к выполнению
    painter->setPen(QPen(Qt::black));
    painter->setFont(QFont("Arial", 10, QFont::Normal));
    painter->drawText(xtext, 45, QString(tr("%1")).arg(TActDur));

    if (apr > -1)
    {
        painter->drawText(xtext, 70, QString(tr("%1")).arg(apr));
    }

}

//==================================================
//==================================================

void Proces::setPriority(int nPriority)
{
    pr = nPriority;
    apr = nPriority;
}

//==================================================
//==================================================

void Proces::changePriority(int nPriority)
{
    apr = nPriority;
}

//==================================================
//==================================================

int Proces::reportNPriority()
{
    return pr;
}

//==================================================
//==================================================

int Proces::reportAPriority()
{
    return apr;
}

//==================================================
//==================================================

int Proces::reportPrTmAct()
{
    // возвращаем время, которе процесс провёл в очереди
    return tq;
}

//==================================================
//==================================================

QColor Proces::reportMyColor()
{
    return MyColor;
}

//==================================================
//==================================================

void Proces::activate()
{
    PrActive = true; // устанавливаем флаг активности
    tq = 0; // время, которое провёл в очереди - в 0
    XVt.append(50*Step); // добавляем координату
}

//==================================================
//==================================================

void Proces::disactivate()
{
    PrActive = false; // сбрасываем флаг активности
    apr = pr; // сбрасываем приоритет
}

//==================================================
//==================================================


void Proces::setQueuePos(int qp)
{
    queuePos = qp; // устанавливаем место в очереди
}

//==================================================
//==================================================

void Proces::slotTime(int nStep)
{
    // если время совпадает cо временем начала работы
    // посылаем сигнал о готовности

    Step = nStep;

    if (Step == PrTmAct)
    {
        emit IMReady(PrID);
        return;
    }

    // если процесс уже активен, то проверяем, выполнился ли он
    // уменьшаем время, оставшееся для выполнения
    // и если оно равно 0, посылаем сигнал о завершении работы
    // иначе увеличиваем время стояния в очереди на 1

    if (PrActive)
    {
        TActDur--;
        if (TActDur == 0)
        {
            emit IFinished(PrID);
            PrActive = false;
            pr = -1;
            apr = -1;
        }
    }
    else
    {
        if (Step > PrTmAct)
        {
            tq++;
        }
    }
}

//==================================================
//==================================================

Proces::~Proces()
{

}
//==============================================================================
