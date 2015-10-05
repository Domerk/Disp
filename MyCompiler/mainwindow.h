#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QString>
#include <lexer.h>

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

    QLabel* LexTableView;

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

public slots:
    void resultsOfLexer(QString);

signals:
    void toLexer(QString);
};

#endif // MAINWINDOW_H
