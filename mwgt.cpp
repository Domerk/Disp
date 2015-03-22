//================================= widget.cpp =================================

#include "mwgt.h"
//==================================================
//=========== ����������� �������� ���� ============
//==================================================
Mwgt::Mwgt(QMainWindow *parent)
    : QMainWindow(parent)
{
    //================== ��������� ���� =====================
    setWindowTitle(tr("��������� �����"));
    setFixedSize(900,490);

    //================== ���������� ���� =====================
    mainWidget = new QWidget();
    mainLayout = new QHBoxLayout();

    disp = new Disp();
    opt = new Options();
 //   opt->show(); // ����� ���������� �� ����, ������ ��� ������ �� � ��

    connect(opt, SIGNAL(sendDO(QVector <int>)), disp, SLOT(slotDO(QVector <int>)));


    //=================== ������ ���� ======================
    menuBar = new QMenuBar();
    // ������ �����
    pmenu = new QMenu(tr("&����"));
    pmenu ->addAction(tr("&�����"),
                      this, SLOT(close()));

    pmenu1 = new QMenu(tr("&��������"));
    pmenu1 ->addAction(tr("&�������� ���������"),
                      this, SLOT(options()));

    // �������� ����� ����
    pmenu3 = new QMenu(tr("&����������"));
    pmenu3 ->addAction(tr("&� ���������"), this,
                       SLOT(label_program()));
    pmenu3 ->addAction(tr("&�����������"), this,
                       SLOT(label_developer()));
    pmenu3 ->addSeparator();
    pmenu3 ->addAction(tr("&������"), this,
                       SLOT(label_help()));
    // ������� ����
    menuBar ->addMenu(pmenu);
    menuBar ->addMenu(pmenu1);

    menuBar ->addMenu(pmenu3);
    this->setMenuBar(menuBar);


    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);


    //==================== lprogram =========================
    lprogram = new QLabel(tr(
"<H2><CENTER>��������� �����</CENTER></H2>"
"<H3><CENTER>Disp 1.0</CENTER></H3>"
"<P>             </P>"
"<P>&nbsp;&nbsp;&nbsp;&nbsp;������ ��������� ������������ �����<BR>"
"&nbsp;&nbsp;&nbsp;&nbsp;��������� ���������� �����,<BR>"
"&nbsp;&nbsp;&nbsp;&nbsp;������������ ����������� ����������<BR>"
"&nbsp;&nbsp;&nbsp;&nbsp;��������������� � ������������� ������������.<BR>"
"&nbsp;&nbsp;&nbsp;&nbsp; <BR>"
"&nbsp;&nbsp;&nbsp;&nbsp;��, ������������ ������ �1, ������� 9.</P>"
"<b><P>&nbsp;&nbsp;&nbsp;&nbsp;������� �� Qt 4.7.4</P></b>"
"<P>&nbsp;&nbsp;&nbsp;&nbsp;������ 1.0<BR>"
"&nbsp;&nbsp;&nbsp;&nbsp;����������: ����� 2015</P>"
                              ));
    lprogram->setWindowFlags(Qt::Window | Qt::WindowSystemMenuHint);
    lprogram->setFixedSize(280,240);
    lprogram->setWindowTitle(tr("� ���������"));
    //=================== ldeveloper ========================
    ldeveloper = new QLabel(tr(
"<B><P><CENTER>��� ����</CENTER>"
"<B><CENTER>�������� �������������� ������</CENTER></B>"
"<B><CENTER>� ����������������</CENTER></P></B>"
"<P><B><CENTER>������� �������������� ������ � �����</CENTER></P></B>"
"<P>&nbsp;&nbsp;&nbsp;&nbsp;�����������: ��������� �����</P>"
"<P>&nbsp;&nbsp;&nbsp;&nbsp;������� ������ �4242</P>"
"<P>&nbsp;&nbsp;&nbsp;&nbsp;�����: ����� 2015</P>"
                                ));
    ldeveloper->setWindowFlags(Qt::Window | Qt::WindowSystemMenuHint);
    ldeveloper->setFixedSize(260,160);
    ldeveloper->setWindowTitle(tr("�����������"));
    //====================== lhelp ==========================
    lhelp = new QLabel(tr(
"<B><P><CENTER><H2>������ � ����������</H2></CENTER></P></B>"
"<P>&nbsp;&nbsp;&nbsp;&nbsp;<b>��������� ��������� ������������ ���������<BR>"
"&nbsp;&nbsp;&nbsp;&nbsp;�������� ��������, �������� �����������.</b></P>"
"<P>&nbsp;&nbsp;&nbsp;&nbsp;- ��� ����, ����� <b>�������� ����� ������</b><BR>"
"&nbsp;&nbsp;&nbsp;&nbsp;������������ ������� ��������� ������� <BR>"
"&nbsp;&nbsp;&nbsp;&nbsp;����������� �������� � ��������������<BR>"
"&nbsp;&nbsp;&nbsp;&nbsp;����: �� ����� 5� ������ ��� �������� � �������<BR>"
"&nbsp;&nbsp;&nbsp;&nbsp;� �� ����� 2� ��� ������ �������.<BR>"
"&nbsp;&nbsp;&nbsp;&nbsp;������� ��������� ��� ������� �������.</P>"
"<P>&nbsp;&nbsp;&nbsp;&nbsp;- ��� ������������ <b>�������� �������<BR>"
"&nbsp;&nbsp;&nbsp;&nbsp;�� ���������</b> ������� �������� + ���������.<BR>"
"&nbsp;&nbsp;&nbsp;&nbsp;<BR>"
"&nbsp;&nbsp;&nbsp;&nbsp;- ���������� <b>�����������</b> �� ������<BR>"
"&nbsp;&nbsp;&nbsp;&nbsp;����� ������������, ������� ��������������<BR>"
"&nbsp;&nbsp;&nbsp;&nbsp;������� ���������. ��� ����� ������ ���� �������.<BR>"
"&nbsp;&nbsp;&nbsp;&nbsp;����� ������� ������������ ���������� �����������.</P>"
"<P>&nbsp;&nbsp;&nbsp;&nbsp;- ��� <b>��������� �������</b> �����������<BR>"
"&nbsp;&nbsp;&nbsp;&nbsp;�������������� ���� ��� -> ��� ����������.<BR>"
"&nbsp;&nbsp;&nbsp;&nbsp;� ����������� ���� �������� ����������, <BR>"
"&nbsp;&nbsp;&nbsp;&nbsp;� ���������� ������������� ������. </P>"
                           ));
    lhelp->setFixedSize(300,340);
    lhelp->setWindowTitle(tr("������"));
    //=======================================================



        mainLayout->addWidget(disp);
    //   mainLayout->addWidget(opt);
        mainWidget->setLayout(mainLayout);
        setCentralWidget(mainWidget);



}
//==================================================
//=========== ������� � ����� � ��������� ==========
//==================================================
void Mwgt::label_program()
{
    lprogram->show();
}
//==================================================
//========== ������� � ����� � ������������ ========
//==================================================
void Mwgt::label_developer()
{
    ldeveloper->show();
}
//==================================================
//============ ������� �� �������� =================
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
//================== ���������� ====================
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
