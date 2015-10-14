#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QMessageBox>
#include <QFont>
#include <QString>
#include <lexer.h>
#include <parser.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    lexer* MyLexer;
    parser* MyParser;

    QLabel* LexTableView;
    QLabel* TreeView;
    QMessageBox* messbox;


private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

public slots:
    void resultsOfLexer(QString);
    void lexicalError(QString);
    void parsError(QString);
    void parsResult(QString);

signals:
    void toLexer(QString);
    void startParser();
};

#endif // MAINWINDOW_H
