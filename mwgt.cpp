//================================= widget.cpp =================================

#include "mwgt.h"
//==================================================
//=========== конструктор главного окна ============
//==================================================
Mwgt::Mwgt(QMainWindow *parent)
    : QMainWindow(parent)
{
    //================== заголовок окна =====================
    setWindowTitle(tr("Диспетчер задач"));
    setFixedSize(900,490);

    //================== содержимое окна =====================
    mainWidget = new QWidget();
    mainLayout = new QHBoxLayout();

    disp = new Disp();
    opt = new Options();
 //   opt->show(); // Пусть вызывается из меню, потому что почемы бы и да

    connect(opt, SIGNAL(sendDO(QVector <int>)), disp, SLOT(slotDO(QVector <int>)));


    //=================== создаём меню ======================
    menuBar = new QMenuBar();
    // первый пункт
    pmenu = new QMenu(tr("&Файл"));
    pmenu ->addAction(tr("&Выход"),
                      this, SLOT(close()));

    pmenu1 = new QMenu(tr("&Процессы"));
    pmenu1 ->addAction(tr("&Создание процессов"),
                      this, SLOT(options()));

    // четвёртый пункт меню
    pmenu3 = new QMenu(tr("&Информация"));
    pmenu3 ->addAction(tr("&О программе"), this,
                       SLOT(label_program()));
    pmenu3 ->addAction(tr("&Разработчик"), this,
                       SLOT(label_developer()));
    pmenu3 ->addSeparator();
    pmenu3 ->addAction(tr("&Помощь"), this,
                       SLOT(label_help()));
    // выводим меню
    menuBar ->addMenu(pmenu);
    menuBar ->addMenu(pmenu1);

    menuBar ->addMenu(pmenu3);
    this->setMenuBar(menuBar);


    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);


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
"<P>&nbsp;&nbsp;&nbsp;&nbsp;<b>Программа позволяет симулировать различные<BR>"
"&nbsp;&nbsp;&nbsp;&nbsp;дорожные ситуации, управляя светофорами.</b></P>"
"<P>&nbsp;&nbsp;&nbsp;&nbsp;- Для того, чтобы <b>изменить время работы</b><BR>"
"&nbsp;&nbsp;&nbsp;&nbsp;определённого сигнала светофора введите <BR>"
"&nbsp;&nbsp;&nbsp;&nbsp;необходимое значение в соотвествующее<BR>"
"&nbsp;&nbsp;&nbsp;&nbsp;поле: не менее 5и секунд для красного и зелёного<BR>"
"&nbsp;&nbsp;&nbsp;&nbsp;и не менее 2х для жёлтого сигнала.<BR>"
"&nbsp;&nbsp;&nbsp;&nbsp;Нажмите Применить для задания времени.</P>"
"<P>&nbsp;&nbsp;&nbsp;&nbsp;- Для установления <b>настроек времени<BR>"
"&nbsp;&nbsp;&nbsp;&nbsp;по умолчнаию</b> нажмите Сбросить + Применить.<BR>"
"&nbsp;&nbsp;&nbsp;&nbsp;<BR>"
"&nbsp;&nbsp;&nbsp;&nbsp;- Количество <b>автомобилей</b> на дороге<BR>"
"&nbsp;&nbsp;&nbsp;&nbsp;можно регулировать, выбирая соотвествующий<BR>"
"&nbsp;&nbsp;&nbsp;&nbsp;уровень сложности. Для этого служит меню Уровень.<BR>"
"&nbsp;&nbsp;&nbsp;&nbsp;Номер уровная соотвествует количеству автомобилей.</P>"
"<P>&nbsp;&nbsp;&nbsp;&nbsp;- Для <b>изменения дизайна</b> автомобилей<BR>"
"&nbsp;&nbsp;&nbsp;&nbsp;воспользуйтесь меню Вид -> Вид автомобиля.<BR>"
"&nbsp;&nbsp;&nbsp;&nbsp;В открывшемся окне выберите автомобиль, <BR>"
"&nbsp;&nbsp;&nbsp;&nbsp;и установите понравившийся дизайн. </P>"
                           ));
    lhelp->setFixedSize(300,340);
    lhelp->setWindowTitle(tr("Помощь"));
    //=======================================================



        mainLayout->addWidget(disp);
    //   mainLayout->addWidget(opt);
        mainWidget->setLayout(mainLayout);
        setCentralWidget(mainWidget);



}
//==================================================
//=========== надпись с инфой о программе ==========
//==================================================
void Mwgt::label_program()
{
    lprogram->show();
}
//==================================================
//========== надпись с инфой о разработчике ========
//==================================================
void Mwgt::label_developer()
{
    ldeveloper->show();
}
//==================================================
//============ надпись со справкой =================
//==================================================
void Mwgt::label_help()
{
    lhelp->show();
}


void Mwgt::options()
{
    opt->show();
}



//==================================================
//================== деструктор ====================
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

}
//==============================================================================
