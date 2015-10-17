#ifndef GEN_H
#define GEN_H

#include <QObject>
#include <QVector>
#include <QString>

class gen : public QObject
{
    Q_OBJECT
public:
    explicit gen(QObject *parent = 0);
    ~gen();

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
        int num;
    };

protected:
    QVector<Element> tree;
    QString* code;

    void genCode();

signals:
    void genError(QString);
    void genResult(QString);

public slots:
    void startGen();
    void treeSlot (QVector<Element>);
};

#endif // GEN_H
