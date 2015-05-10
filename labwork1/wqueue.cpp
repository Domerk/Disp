//================================= wqueue.cpp =================================

#include "wqueue.h"


Wqueue::Wqueue(QWidget *parent)
    : QWidget(parent)
{
    painter = new QPainter(); //художник
    // устанавливаем цвет фона
    pal.setColor(this->backgroundRole(), Qt::white);
    this->setPalette(pal);
    this->setAutoFillBackground(true);

    // устанавливаем начальные размеры виджета
    wheight = 300;
    wwidth = 600;

    this->resize(wwidth, wheight);

    hr = 30; // размеры прямоугольников, которые будем рисовать
    wr = 50;
}

//==================================================
//==================================================

void Wqueue::paintEvent(QPaintEvent* event)
{
    painter->begin(this); //начинаем рисовать в окне

    if(!xproces.empty()) // если очередь не пуста
    {
        int n = xproces.size(); // узнаём размер
        int y = 41; // устанавливаем размер отступа от края
        // и рисуем первый прямоугольник - процесс
        painter->setPen(QPen(colors.at(0),1));
        painter->setBrush(QBrush(colors.at(0)));
        painter->drawRect(xproces.at(0)*wr,y,wr,hr);
        y+=hr; // увеличиваем координату y на его высоту

        if (n>1) // если есть ещё процессы, то для всех
        {
            for (int i = 1; i<n; i++)
            {
                // проверяем выход за гаринцы окна
                if (xproces.at(i)*wr >= wwidth-2*wr)
                {
                    // если нужно растягиваем окно
                    wwidth = wwidth + wr;
                    this->resize(wwidth, wheight);
                }
                // устанавливаем параметры кисти
                painter->setPen(QPen(colors.at(i),1));
                painter->setBrush(QBrush(colors.at(i)));

                // если так текущего процесса совпадает с тактом предыдущего
                if(xproces.at(i) == xproces.at(i-1))
                {
                    if(y+hr>=wheight) // проверяем выход за границу по вертикали
                    {
                        // если нужно, растягиваем окно
                        wheight = wheight + hr;
                        this->resize(wwidth, wheight);
                    }
                    // рисуем процесс, увеличиваем y на его высоту
                    painter->drawRect(xproces.at(i)*wr,y,wr,hr);
                    y+=hr;

                }
                else // иначе сбрасываем y и рисуем процесс
                {
                    y = 41;
                    painter->drawRect(xproces.at(i)*wr,y,wr,hr);
                    y+=hr;
                }

            }
        }

    }
    // рисуем линеечку
    painter->setPen(QPen(Qt::black,2));
    painter->drawLine(0, 40, wwidth, 40);
    // устанавливаем параметры текста
    painter->setPen(QPen(Qt::black,1));
    painter->setPen(QPen(Qt::black,1));
    painter->setFont(QFont("Arial", 10, QFont::Normal));
    // задаём шаг и счётчик
    int ix = wr;
    int i = 1;
    // рисуем ризки и цифры
    while (ix<wwidth)
    {
        painter->drawLine(ix, 30, ix, 50);
        painter->drawText(ix-2, 20, QString(tr("%1")).arg(i));
        ix+=wr;
        i++;
    }

    painter->end();
}

//==================================================
//==================================================

void Wqueue::SlotQueue(int nStep, QColor nColor)
{
    // если процесс стоит в очереди, то приходит инфа о номере такта
    // и о цвете, закреплённым за этим процессом
    xproces.push_back(nStep); // добавляем в конец
    colors.push_back(nColor); // добавляем в конец

    repaint(); // перерисовать
}

//==================================================
//==================================================

Wqueue::~Wqueue()
{
    delete painter;
}
//==============================================================================
