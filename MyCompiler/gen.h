#ifndef GEN_H
#define GEN_H

#include <QObject>
#include <QVector>
#include <QString>
#include <QMap>

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
    QVector<QString> objCode;
    QVector<QString> optCode;
    QMap<QString, QString> replaceTable;
    QString* code1;
    QString* code2;

    void genCode(QVector<Element> phrase);
    void review();
    void result();

signals:
    void genError(QString);
    void genResult(QString, QString);

public slots:
    void startGen();
    void treeSlot (QVector<Element>);
};

#endif // GEN_H
