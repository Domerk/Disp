#ifndef LEXER_H
#define LEXER_H

#include <QObject>
#include <QVector>
#include <QString>
#include <QStringList>
#include <QRegularExpression>

class lexer: public QObject
{ 
    Q_OBJECT

public:
    lexer(QObject *parent = 0);
    ~lexer();

    struct Lexeme
    {
        QString lexeme;
        QString type;
    };

protected:
    QVector <Lexeme> lexTable; // таблица лексем
    QVector <QString> thisIsFail; // подстроки, содержащие ошибки
    QString text; // исходный текст
    QString textCopy;

    QRegularExpression* keyword; // ключевые слова
    QRegularExpression* number; // латинские цифры
    QRegularExpression* identifier; // идентификаторы
    QRegularExpression* comparisonSign; // знаки сравнения

    void analyze();
    void result();
    void addLexToTable(QString nLex, QString nType);

public slots:
    void textSlot (QString newText); // слот, принимающий текст для анализа

signals:
    void tableSignal (QString); // сигнал, передающий таблицу лексем в виде строки
    void failSignal (QString);
    void lexTableSignal(QVector);

};

#endif // LEXER_H
