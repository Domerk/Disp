#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MyLexer = new lexer();

    connect(this, SIGNAL(toLexer(QString)), MyLexer, SLOT(textSlot(QString)));

}

MainWindow::~MainWindow()
{
    delete ui;
    delete MyLexer;
}

void MainWindow::on_pushButton_clicked()
{
    QString text = ui->textEdit->toPlainText();
    emit toLexer(text);
}
