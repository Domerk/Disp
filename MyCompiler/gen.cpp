#include "gen.h"

gen::gen(QObject *parent) : QObject(parent)
{
    code = new QString();
}

gen::~gen()
{
    delete code;
}

void gen::treeSlot (QVector<Element> newTree)
{
    tree = newTree;
}

void gen::startGen()
{
    if (tree.isEmpty())
    {
        QString str;
        str.append(tr("Отсутсвуют данные синтаксического анализа!"));
        emit genError(str);
        return;
    }
    genCode();
}

void gen::genCode()
{
    for (Element & elem: tree)
    {
        if (elem.num == 3 || elem.num == 5)
        {
            code->append("mov ");
            code->append(elem.expression[0].lexeme);
            code->append(", ");
            code->append(elem.expression[2].lexeme);
            code->append(";\n");
            continue;
        }

    }
    emit genResult(*code);
    code->clear();
}
