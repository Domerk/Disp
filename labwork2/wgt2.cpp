//================================= wgt2.cpp =================================

#include "wgt2.h"

Wgt::Wgt(QWidget *parent) :
    QWidget(parent)
{
    // устанавливем цвет фона виджета - белый
    pal.setColor(this->backgroundRole(), Qt::white);
    this->setPalette(pal);
    this->setAutoFillBackground(true);

    // создаём объект симулятора
    sim = new Sim();
    // и помещаем его в поток
    sim->moveToThread(&simThread);
    // соединяем сигналы и слоты
    connect (sim, SIGNAL(finished()), this, SLOT(prFinished()));
    // фиксиуем размер виджета
    this->setFixedSize(940,540);

    // прогресс-бары добавляем в контейнер
    pbMap.insert('A', new QProgressBar());
    pbMap.insert('B', new QProgressBar());
    pbMap.insert('C', new QProgressBar());
    pbMap.insert('D', new QProgressBar());
    pbMap.insert('E', new QProgressBar());
    pbMap.insert('F', new QProgressBar());
    pbMap.insert('G', new QProgressBar());
    pbMap.insert('H', new QProgressBar());
    pbMap.insert('I', new QProgressBar());

    // коннектим
    for (QProgressBar *pb : pbMap)
        connect(sim, SIGNAL(progressChanged(char,int)),
                this, SLOT(setProgress(char,int)));

    // Надписи добавляем в контейнер надписей
    labelMap.insert('A', new QLabel(tr("A:")));
    labelMap.insert('B', new QLabel(tr("B:")));
    labelMap.insert('C', new QLabel(tr("C:")));
    labelMap.insert('D', new QLabel(tr("D:")));
    labelMap.insert('E', new QLabel(tr("E:")));
    labelMap.insert('F', new QLabel(tr("F:")));
    labelMap.insert('G', new QLabel(tr("G:")));
    labelMap.insert('H', new QLabel(tr("H:")));
    labelMap.insert('I', new QLabel(tr("I:")));

    hblMap.insert('A', new QHBoxLayout());
    hblMap.insert('B', new QHBoxLayout());
    hblMap.insert('C', new QHBoxLayout());
    hblMap.insert('D', new QHBoxLayout());
    hblMap.insert('E', new QHBoxLayout());
    hblMap.insert('F', new QHBoxLayout());
    hblMap.insert('G', new QHBoxLayout());
    hblMap.insert('H', new QHBoxLayout());
    hblMap.insert('I', new QHBoxLayout());

    // добавляем виджеты в компановку
    for (char c = 'A'; c <= 'I'; c++)
    {
        hblMap[c]->addWidget(labelMap[c]);
        hblMap[c]->addWidget(pbMap[c]);
    }

    // картинка с исходными данными варианта
    processImage = new QGraphicsPixmapItem(QPixmap("://img1.PNG"));
    scene = new QGraphicsScene();
    view = new QGraphicsView(scene);
    scene->addItem(processImage);

    // заголовок
    processLabel = new QLabel(tr("<h3>Граф задач:</h3>"));

    // отправляем всё это в компановку
    vLayout = new QVBoxLayout();
    vLayout->addWidget(processLabel);
    vLayout->addWidget(view);

    for (QHBoxLayout* hbl : hblMap)
        vLayout->addLayout(hbl);

    hLayout = new QHBoxLayout();

    // создаём кнопки
    button1 = new QPushButton(tr("Старт"));
    button1->setFixedSize(90, 25);
    connect (button1, SIGNAL(clicked()), this, SLOT(start()));

    button2 = new QPushButton(tr("Показать лог"));
    button2->setFixedSize(90, 25);
    button2->setEnabled(false); // не активна
    connect (button2, SIGNAL(clicked()), this, SLOT(log()));

    button3 = new QPushButton(tr("Сброс"));
    button3->setFixedSize(90, 25);
    button3->setEnabled(false); // не активна
    connect (button3, SIGNAL(clicked()), this, SLOT(restart()));

    // Добавляем кнопки в компановку
    lbl = new QLabel(tr("<h3>Опции: </h3>"));
    hLayout->addWidget(lbl);
    hLayout->addWidget(button1);
    hLayout->addSpacing(10);
    hLayout->addWidget(button2);
    hLayout->addSpacing(10);
    hLayout->addWidget(button3);
    hLayout->setAlignment(Qt::AlignLeft); // по левому краю

    vLayout->addLayout(hLayout);

    mainLayout = new QHBoxLayout();
    mainLayout->addLayout(vLayout);

    // отобразим картинку с таблицей, хотя не понятно, зачем она нужна
    table = new QLabel;
    table->setPixmap(QPixmap("://img2.PNG"));
    mainLayout->addWidget(table);

    this->setLayout(mainLayout);
}

// ============================================

void Wgt::setProgress(char process, int progress)
{
    // устанавливаем прогесс-бару принятое значение
    pbMap[process]->setValue(progress);
}

// ============================================

void Wgt::start()
{
    // запускаем, делаем неактивными кнопки
    sim->start();
    button1->setEnabled(false);
    button2->setEnabled(false);
}

// ============================================

void Wgt::log()
{
    // здесь считываем текст из файла
    // и отображаем его в окошке
    QTextStream stream;
    textEdit = new QTextEdit;
    logFile.setFileName(tr("log.txt"));

    if (!logFile.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            return;
        }
        stream.setDevice(&logFile);

    while (!stream.atEnd())
        {
            QString line = stream.readLine();
            textEdit->append(line);
        }
    // textEdit - тот же виджет
    textEdit->setWindowTitle(tr("Лог"));
    textEdit->setReadOnly(false);
    textEdit->show(); // показываем
}

// ============================================

void Wgt::restart()
{
    // сбрасываем значения прогресс-баров
    for (char c = 'A'; c <= 'I'; c++)
    {
        pbMap[c]->setValue(0);
    }

    delete textEdit; // удаляем окошко с логом
    // меняем состояния кнопок
    button1->setEnabled(true);
    button3->setEnabled(false);
}

// ============================================

void Wgt::prFinished()
{
    // делаем кнопки доступными
    button2->setEnabled(true);
    button3->setEnabled(true);
}

// ============================================

Wgt::~Wgt()
{
    delete processImage;
    delete scene;
    delete view;
    delete processLabel;

    for (QProgressBar *pb : pbMap)
        delete pb;

    for (QLabel *l : labelMap)
        delete l;

    for (QHBoxLayout *hbl : hblMap)
        delete hbl;

    delete vLayout;
    delete hLayout;
    delete mainLayout;
    delete button1;
    delete button2;
    delete button3;
    delete sim;
    delete table;
    delete lbl;
    delete textEdit;
}
//==============================================================================

