#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include <QVector>
#include <QString>

class parser: public QObject
{
    Q_OBJECT

public:
    parser(QObject *parent = 0);
    ~parser();

    struct Lexeme
    {
        QString lexeme;
        QString type;
    };

protected:
    QVector <Lexeme> lexTable; // таблица лексем

    void analize();

    bool thisIsS(QVector <Lexeme>);
    bool thisIsF(QVector <Lexeme>);
    bool thisIsT(QVector <Lexeme>);
    bool thisIsE(QVector <Lexeme>);

public slots:
    void lexTableSlot(QVector <Lexeme>);
    void startParser();

signals:
    void parsError(QString);

};

#endif // PARSER_H
