//================================= mwgt.cpp =================================

#include "mwgt.h"

Mwgt::Mwgt(QMainWindow *parent)
    : QMainWindow(parent)
{
    //================== заголовок окна =====================
    setWindowTitle(tr("Параллельные процессы"));
    setFixedSize(950,570);



    wgt = new Wgt;
    setCentralWidget(wgt);



    //=================== создаём меню ======================
        menuBar = new QMenuBar();
        // первый пункт
        pmenu = new QMenu(tr("Файл"));
        pmenu ->addAction(tr("Выход"),
                          this, SLOT(close()));



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

        menuBar ->addMenu(pmenu3);
        this->setMenuBar(menuBar);

        //==================== lprogram =========================
        lprogram = new QLabel(tr(
                                  "<H2><CENTER>Параллельные процессы</CENTER></H2>"
                                  "<H3><CENTER>Thr 1.0</CENTER></H3>"
                                  "<P>             </P>"
                                  "<P>&nbsp;&nbsp;&nbsp;&nbsp;Данная программа представляет собой<BR>"
                                  "&nbsp;&nbsp;&nbsp;&nbsp;демонстрацию возможностей<BR>"
                                  "&nbsp;&nbsp;&nbsp;&nbsp;распараллеливания процессов<BR>"
                                  "&nbsp;&nbsp;&nbsp;&nbsp;с использованием С++ и Qt.<BR>"
                                  "&nbsp;&nbsp;&nbsp;&nbsp; <BR>"
                                  "&nbsp;&nbsp;&nbsp;&nbsp;ОС, лабораторная работа №2, вариант 9.</P>"
                                  "<b><P>&nbsp;&nbsp;&nbsp;&nbsp;Основан на Qt 5.2</P></b>"
                                  "<P>&nbsp;&nbsp;&nbsp;&nbsp;Версия 1.0<BR>"
                                  "&nbsp;&nbsp;&nbsp;&nbsp;Разработка: Весна 2015</P>"
                                  ));

        lprogram->setFixedSize(250,240);
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

        ldeveloper->setFixedSize(260,160);
        ldeveloper->setWindowTitle(tr("Разработчик"));


        //====================== lhelp ==========================
        lhelp = new QLabel(tr(
                               "<B><P><CENTER><H2>Работа с программой</H2></CENTER></P></B>"
                               "<P>&nbsp;&nbsp;&nbsp;&nbsp;Для запуска параллельных процессов необходимо нажать<BR>"
                               "&nbsp;&nbsp;&nbsp;&nbsp;кнопку <b>Старт</b>.</P>"
                               "<P>&nbsp;&nbsp;&nbsp;&nbsp;После завершения последнего процесса станут доступны<BR>"
                               "&nbsp;&nbsp;&nbsp;&nbsp;кнопки <b>Показать лог</b> и <b>Сброс</b>.</P>"
                               "<P>&nbsp;&nbsp;&nbsp;&nbsp;После выполнения команды сброса можно запустить<BR>"
                               "&nbsp;&nbsp;&nbsp;&nbsp;повторную работу процессов.</P>"
                               "<P>&nbsp;&nbsp;&nbsp;&nbsp;Обратите внимание, что используемый в программе <BR>"
                               "&nbsp;&nbsp;&nbsp;&nbsp;withQtConcurrent автоматически корректирует число<BR>"
                               "&nbsp;&nbsp;&nbsp;&nbsp;активных потоков в зависимости от количесва доступных<BR>"
                               "&nbsp;&nbsp;&nbsp;&nbsp;ядер процессора.<BR>"

                               ));
        lhelp->setFixedSize(330,240);
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

Mwgt::~Mwgt()
{
    delete menuBar; // меню
    delete pmenu; // пункты меню
    delete pmenu1;
    delete pmenu2;
    delete pmenu3;
    delete lprogram; // надписи
    delete ldeveloper;
    delete lhelp;
    delete wgt;
    delete mainLayout;

}
//==============================================================================
