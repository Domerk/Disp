#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MyLexer = new lexer();
    LexTableView = new QLabel();

    connect(this, SIGNAL(toLexer(QString)), MyLexer, SLOT(textSlot(QString)));
    connect (MyLexer, SIGNAL(tableSignal(QString)), this, SLOT(resultsOfLexer(QString)));

}

MainWindow::~MainWindow()
{
    delete ui;
    delete MyLexer;
    delete LexTableView;
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
