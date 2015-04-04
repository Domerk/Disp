//================================= opstep.cpp =================================

#include "opstep.h"

const int MIN_STEP = 2;
const int MAX_STEP = 8;


OpStep::OpStep(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(180,120); // фиксированный размер
    setWindowTitle(tr("Параметры"));
    // в качестве параметров виджета задаём ему его тип
    // он будет окном со скрытым системным меню
    // то есть оставляем только кнопку закрытия
    // а остальные кнопки не выводятся
    setWindowFlags(Qt::Window | Qt::WindowSystemMenuHint);

    vb = new QVBoxLayout(); // вертикальна¤ компановка

    vb->setSpacing(15);

    lTxt = new QLabel(tr("Время пересчёта приоритета:"));

    vb->addWidget(lTxt);

    // для ввода числового значения используем спинбокс
    // устанавливаем ему значение по-умолчанию (3)
    // а также минимимально и макимсально возмножные значения
    SBt = new QSpinBox();
    SBt->setMinimum(MIN_STEP);
    SBt->setValue(3);
    SBt->setMaximum(MAX_STEP);

    vb->addWidget(SBt);

    // создаём кнопочку
    pb = new QPushButton (tr("Установить")); // кнопка "Сброс настроек"
    vb->addWidget(pb);
    connect(pb, SIGNAL(clicked()), SLOT(slotOS()));

    this->setLayout(vb);
}

//==================================================
//==================================================

void OpStep::slotOS()
{
    // если кнопка нажата, посылаем сигнал
    // и закрываем окошко, чтобы не болталось
    emit signalOS(SBt->value());
    this->hide();
}

//==================================================
//==================================================

OpStep::~OpStep()
{
    delete vb;
    delete pb;
    delete SBt;
    delete lTxt;
}
//==============================================================================
