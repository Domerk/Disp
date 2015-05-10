//================================= mwgt.cpp =================================

#include "mwgt.h"

Mwgt::Mwgt(QMainWindow *parent)
    : QMainWindow(parent)
{
    //================== заголовок окна =====================
    setWindowTitle(tr("Диспетчер задач"));
    setFixedSize(920,520);

    //================== содержимое окна =====================
    mainWidget = new QWidget();
    mainLayout = new QHBoxLayout();
    // задаём цвет фона - белый
    pal.setColor(this->backgroundRole(), Qt::white);
    this->setPalette(pal);
    this->setAutoFillBackground(true);

    disp = new Disp(); // создаём диспетчер

    opt = new Options(); // создаём настройки
    connect(opt, SIGNAL(sendDO(QVector <int>)), disp, SLOT(slotDO(QVector <int>)));
    connect(opt, SIGNAL(SSTOP()), this, SLOT(slotSTOP()));

    ost = new OpStep(); // и ещё одни настройки
    connect(ost, SIGNAL(signalOS(int)), disp, SLOT(slotOS(int)));

    wque = new Wqueue(); // создаём график очереди
    connect(disp, SIGNAL(signalQueue(int,QColor)), wque, SLOT(SlotQueue(int,QColor)));
    wque->setMinimumSize(400,200); // минимальный размер

    qsa = new QScrollArea(); // создаём окно видовой прокрутки
    qsa->setWindowTitle(tr("График очереди"));
    qsa->setPalette(pal); // устанавливаем цвет фона
    qsa->setAutoFillBackground(true);
    qsa->resize(605, 305); // размер не фикисрованный
    qsa->setMinimumSize(300,150); // минимально возможный
    qsa->setWidget(wque); // отправляем в него очередь

    // компановка в целом здесь не нужна, тк в главном окне всего 1 виджет
    // но таким образом мы может управлять его размещением
    // и получаем возможность при необходимости вставтить ещё виджеты
    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);

    mainLayout->addWidget(disp);
    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);

    //=================== создаём меню ======================
    menuBar = new QMenuBar();
    // первый пункт
    pmenu = new QMenu(tr("Файл"));
    pmenu ->addAction(tr("Выход"),
                      this, SLOT(close()));

    pmenu1 = new QMenu(tr("Процессы"));
    pmenu1 ->addAction(tr("Создание процессов"),
                       this, SLOT(options()));
    pmenu1 ->addAction(tr("График очереди"),
                       this, SLOT(opwqueue()));

    pmenu2 = new QMenu(tr("Настройки"));
    pmenu2->addAction(tr("Параметры"),
                      this, SLOT(opsteps()));

    // четвёртый пункт меню
    pmenu3 = new QMenu(tr("Информация"));
    pmenu3 ->addAction(tr("О программе"), this,
                       SLOT(label_program()));
    pmenu3 ->addAction(tr("Разработчик"), this,
                       SLOT(label_developer()));
    pmenu3 ->addSeparator();
    pmenu3 ->addAction(tr("Помощь"), this,
                       SLOT(label_help()));
    // выводим меню
    menuBar ->addMenu(pmenu);
    menuBar ->addMenu(pmenu1);
    menuBar ->addMenu(pmenu2);
    menuBar ->addMenu(pmenu3);
    this->setMenuBar(menuBar);

    //==================== lprogram =========================
    lprogram = new QLabel(tr(
                              "<H2><CENTER>Диспетчер задач</CENTER></H2>"
                              "<H3><CENTER>Disp 1.0</CENTER></H3>"
                              "<P>             </P>"
                              "<P>&nbsp;&nbsp;&nbsp;&nbsp;Данная программа представляет собой<BR>"
                              "&nbsp;&nbsp;&nbsp;&nbsp;симулятор диспетчера задач,<BR>"
                              "&nbsp;&nbsp;&nbsp;&nbsp;использующий вытесняющую дисциплину<BR>"
                              "&nbsp;&nbsp;&nbsp;&nbsp;диспетчеризации с динамическими приоритетами.<BR>"
                              "&nbsp;&nbsp;&nbsp;&nbsp; <BR>"
                              "&nbsp;&nbsp;&nbsp;&nbsp;ОС, лабораторная работа №1, вариант 9.</P>"
                              "<b><P>&nbsp;&nbsp;&nbsp;&nbsp;Основан на Qt 4.7.4</P></b>"
                              "<P>&nbsp;&nbsp;&nbsp;&nbsp;Версия 1.0<BR>"
                              "&nbsp;&nbsp;&nbsp;&nbsp;Разработка: Весна 2015</P>"
                              ));
    lprogram->setWindowFlags(Qt::Window | Qt::WindowSystemMenuHint);
    lprogram->setFixedSize(280,240);
    lprogram->setWindowTitle(tr("О программе"));


    //=================== ldeveloper ========================
    ldeveloper = new QLabel(tr(
                                "<B><P><CENTER>СПб ГУАП</CENTER>"
                                "<B><CENTER>Институт вычислительных систем</CENTER></B>"
                                "<B><CENTER>и программирования</CENTER></P></B>"
                                "<P><B><CENTER>Кафедра вычислительных систем и сетей</CENTER></P></B>"
                                "<P>&nbsp;&nbsp;&nbsp;&nbsp;Разработчик: Максимова Ольга</P>"
                                "<P>&nbsp;&nbsp;&nbsp;&nbsp;Учебная группа №4242</P>"
                                "<P>&nbsp;&nbsp;&nbsp;&nbsp;Время: Весна 2015</P>"
                                ));
    ldeveloper->setWindowFlags(Qt::Window | Qt::WindowSystemMenuHint);
    ldeveloper->setFixedSize(260,160);
    ldeveloper->setWindowTitle(tr("Разработчик"));


    //====================== lhelp ==========================
    lhelp = new QLabel(tr(
                           "<B><P><CENTER><H2>Работа с программой</H2></CENTER></P></B>"
                           "<P>&nbsp;&nbsp;&nbsp;&nbsp;Программа представляет собой симулятор<BR>"
                           "&nbsp;&nbsp;&nbsp;&nbsp;диспетчера задач с динамическими приоритетами,<BR>"
                           "&nbsp;&nbsp;&nbsp;&nbsp;вычисляемыми по формуле pi = pi-1 + ai*t*t.</P>"
                           "<P>&nbsp;&nbsp;&nbsp;&nbsp;Для создания процессов зайдите в меню <B>Процессы</B><BR>"
                           "&nbsp;&nbsp;&nbsp;&nbsp;и выберите пункт <B>Создание процессов</B>.<BR>"
                           "&nbsp;&nbsp;&nbsp;&nbsp;Процесс считается созданным, если его длительность<BR>"
                           "&nbsp;&nbsp;&nbsp;&nbsp;не равно 0.</P>"
                           "<P>&nbsp;&nbsp;&nbsp;&nbsp;Для применения изменений нажмите кнопку <B>Старт</B>,<BR>"
                           "&nbsp;&nbsp;&nbsp;&nbsp;для остановки работы Диспетчера - кнопку <B>Сброс</B>.</P>"
                           "<P>&nbsp;&nbsp;&nbsp;&nbsp;Для просмотра графика изменений очереди процессов<BR>"
                           "&nbsp;&nbsp;&nbsp;&nbsp;во времени используйте <B>График очереди</B> из меню<BR>"
                           "&nbsp;&nbsp;&nbsp;&nbsp;<B>Процессы</B>.</P>"
                           "<P>&nbsp;&nbsp;&nbsp;&nbsp;Для изменения интервала пересчёта приоритета<BR>"
                           "&nbsp;&nbsp;&nbsp;&nbsp;зайдите в меню <B>Настройки</B> и выберите пункт<BR>"
                           "&nbsp;&nbsp;&nbsp;&nbsp;<B>Параметры</B>. Обратите внимание, что интервал<BR>"
                           "&nbsp;&nbsp;&nbsp;&nbsp;не может быть равен 1!<BR></P>"
                           ));
    lhelp->setFixedSize(300,330);
    lhelp->setWindowTitle(tr("Помощь"));

    //=======================================================

}

//==================================================
//==================================================
void Mwgt::label_program()
{
    lprogram->show();
}

//==================================================
//==================================================
void Mwgt::label_developer()
{
    ldeveloper->show();
}

//==================================================
//==================================================
void Mwgt::label_help()
{
    lhelp->show();
}

//==================================================
//==================================================
void Mwgt::options()
{
    opt->show();
}

//==================================================
//==================================================
void Mwgt::slotSTOP()
{
    // для сброса просто удаляем диспетчер и очередь
    // и создаём их заново
    // не забываем соединить сигналы и слоты
    delete disp;
    disp = new Disp();
    connect(opt, SIGNAL(sendDO(QVector <int>)), disp, SLOT(slotDO(QVector <int>)));
    mainLayout->addWidget(disp);

    delete wque;
    wque = new Wqueue();
    connect(disp, SIGNAL(signalQueue(int,QColor)), wque, SLOT(SlotQueue(int,QColor)));
    wque->setMinimumSize(400,200);
    qsa->resize(605, 305);
    qsa->setWidget(wque);

}

//==================================================
//==================================================
void Mwgt::opsteps()
{
    ost->show();
}

//==================================================
//==================================================
void Mwgt::opwqueue()
{
    qsa->show();
}

//==================================================
//==================================================
Mwgt::~Mwgt()
{
    delete menuBar;
    delete pmenu;
    delete pmenu1;
    delete pmenu2;
    delete pmenu3;
    delete lprogram;
    delete ldeveloper;
    delete lhelp;
    delete mainLayout;

    delete mainWidget;

    delete disp;
    delete opt;
    delete ost;
    delete wque;
    delete qsa;

}
//==============================================================================
