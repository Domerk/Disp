#ifndef PARSER_H
#define PARSER_H

#include <QObject>

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

public slots:
    void lexTableSlot(QVector);

};

#endif // PARSER_H
