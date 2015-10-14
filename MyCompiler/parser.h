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

    struct Element
    {
        QVector <Lexeme> expression;
        QString type;
        bool terminate;
        int layer;
    };

protected:
    QVector <Lexeme> lexTable; // таблица лексем
    QVector <Element> tree;

    void analize();
    void result();
    void addInTree(QVector <Lexeme>, QString, bool, int);

    bool thisIsS(QVector <Lexeme>);
    bool thisIsF(QVector <Lexeme>, int);
    bool thisIsT(QVector <Lexeme>, int);
    bool thisIsE(QVector <Lexeme>, int);

public slots:
    void lexTableSlot(QVector <Lexeme>);
    void startParser();

signals:
    void parsError(QString);
    void parsResult(QString);

};

#endif // PARSER_H
