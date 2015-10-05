#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MyLexer = new lexer();
    LexTableView = new QLabel();

    QFont font = LexTableView->font();
    font.setPixelSize(12);
    LexTableView->setFont(font);
    LexTableView->setWindowTitle(tr("Таблица лексем"));

    messbox = new QMessageBox();
    messbox->setFont(font);

    connect(this, SIGNAL(toLexer(QString)), MyLexer, SLOT(textSlot(QString)));
    connect (MyLexer, SIGNAL(tableSignal(QString)), this, SLOT(resultsOfLexer(QString)));
    connect (MyLexer, SIGNAL(failSignal(QString)), this, SLOT(lexicalError(QString)));

}

MainWindow::~MainWindow()
{
    delete ui;
    delete MyLexer;
    delete LexTableView;
    delete messbox;
}

void MainWindow::on_pushButton_clicked()
{
    QString text = ui->textEdit->toPlainText();
    emit toLexer(text);
}

void MainWindow::on_pushButton_2_clicked()
{
    LexTableView->show();
}

void MainWindow::resultsOfLexer(QString forTable)
{
    LexTableView->setText(forTable);
}

void MainWindow::lexicalError(QString txt)
{
    messbox->setText(tr("В ходе выполнения лексического анализа были обнаружены ошибки!"));
    messbox->setWindowTitle(tr("Сообщение об ошибке"));
    messbox->show();

    ui->textEdit->setHtml(txt);
}
