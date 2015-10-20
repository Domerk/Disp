#include "gen.h"

gen::gen(QObject *parent) : QObject(parent)
{
    code1 = new QString();
    code2 = new QString();
    numLayout = 0;
}

gen::~gen()
{
    delete code1;
    delete code2;
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
    review();
    result();
}

void gen::review()
{
    QVector<Element>phrase;

    for (Element & elem: tree)
    {
        if (elem.num == 0 && !phrase.isEmpty())
        {
            genCode(phrase);
            phrase.clear();
        }
        else
        {
            phrase.append(elem);
        }
    }
}

void gen::genCode(QVector<Element>phrase)
{
    int n = phrase.size();
    int i = 0;
    if (n>0)
    {
        //==========================================
        if (phrase[i].num == 3 || phrase[i].num == 5)
        {
            objCode.append("mov ");
            objCode.append(phrase[i].expression[0].lexeme);
            objCode.append(", ");
            objCode.append(phrase[i].expression[2].lexeme);
            objCode.append("\n");

            optCode.append("mov ");

            // Пришедщая фраза a := b
            // Если в таблице замен переменной b не сопоставлено занчение
            if (replaceTable[phrase[i].expression[2].lexeme].isNull())
            {
                // Заносим его в оптимизированный код как оно есть
                optCode.append(phrase[i].expression[0].lexeme);
                optCode.append(", ");
                optCode.append(phrase[i].expression[2].lexeme);

                // И если b - число, а уровень вложенности 0, то заносим в таблицу замен пару a | b
                if (phrase[i].layer == 0 && phrase[i].expression[2].type == "Number")
                    replaceTable.insert(phrase[i].expression[0].lexeme, phrase[i].expression[2].lexeme);

                // Если b - не число, и в таблице есть запись для a, то удаляем эту запись
                if (phrase[i].expression[2].type != "Number" && !replaceTable[phrase[i].expression[0].lexeme].isNull())
                    replaceTable.erase(replaceTable.find(phrase[i].expression[0].lexeme));
            }
            else
            {
                // Иначе, если в таблице уже есть запись для b
                // То подставляем вместо b соответсвующее значение
                optCode.append(phrase[i].expression[0].lexeme);
                optCode.append(", ");
                optCode.append(replaceTable.value(phrase[i].expression[2].lexeme));

                // И если уровень вложенности 0, то заносим в таблицу замен пару a | b
                if (phrase[i].layer == 0 && phrase[i].expression[2].type == "Number")
                    replaceTable.insert(phrase[i].expression[0].lexeme, replaceTable.value(phrase[i].expression[2].lexeme));
            }

            optCode.append("\n");
            return;
        }

        //==========================================

        if (phrase[i].num == 6 || phrase[i].num == 7 || phrase[i].num == 8)
        {
            objCode.append("cmp ");
            objCode.append(phrase[i].expression[0].lexeme);
            objCode.append(", ");
            objCode.append(phrase[i].expression[2].lexeme);

            optCode.append("cmp ");

            if (!replaceTable[phrase[i].expression[0].lexeme].isNull())
                optCode.append(replaceTable.value(phrase[i].expression[0].lexeme));
            else
                optCode.append(phrase[i].expression[0].lexeme);

            optCode.append(", ");

            if (!replaceTable[phrase[i].expression[2].lexeme].isNull())
                optCode.append(replaceTable.value(phrase[i].expression[2].lexeme));
            else
                optCode.append(phrase[i].expression[2].lexeme);

            if (phrase[i].num == 6)
            {
                objCode.append("\njg ");
                optCode.append("\njg ");
            }

            if (phrase[i].num == 7)
            {
                objCode.append("\njl ");
                optCode.append("\njl ");
            }

            if (phrase[i].num == 8)
            {
                objCode.append("\njnz ");
                optCode.append("\njnz ");
            }
            return;
        }

        //==========================================

        if (phrase[i].num == 1 || phrase[i].num == 4)
        {
            int nl = numLayout;
            numLayout +=2;
            if (phrase[i].expression[0].lexeme == "if")
            {
                QVector<Element>ph;
                int layer = phrase[i].layer;
                i++;
                while (phrase[i].expression[0].lexeme != "then" && phrase[i].layer != layer)
                {
                    ph.append(phrase[i]);
                    i++;
                }
                genCode(ph);
                objCode.append("label" + QString::number(nl) + "\n");
                optCode.append("label" + QString::number(nl) + "\n");
            }

            if (phrase[i].expression[0].lexeme == "then")
            {
                QVector<Element>ph;
                int layer = phrase[i].layer;
                i++;

                while (phrase[i].layer > layer)
                {
                    ph.append(phrase[i]);
                    i++;
                }
                genCode(ph);
                objCode.append("jmp label" + QString::number(nl+1) + "\n\nlabel" + QString::number(nl) + ":\n");
                optCode.append("jmp label" + QString::number(nl+1) + "\n\nlabel" + QString::number(nl) + ":\n");
            }

            if (phrase[i].expression[0].lexeme == "else")
            {
                QVector<Element>ph;
                int layer = phrase[i].layer;
                i++;
                while (i < n && phrase[i].layer > layer)
                {
                    ph.append(phrase[i]);
                    i++;
                }
                genCode(ph);
                objCode.append("\nlabel" + QString::number(nl+1) + ":\n");
                optCode.append("\nlabel" + QString::number(nl+1) + ":\n");

            }
            return;
        }

        //==========================================

        if (phrase[i].num == 2)
        {
            int nl = numLayout;
            numLayout ++;
            if (phrase[i].expression[0].lexeme == "if")
            {
                QVector<Element>ph;
                int layer = phrase[i].layer;
                i++;
                while (phrase[i].layer > layer)
                {
                    ph.append(phrase[i]);
                    i++;
                }
                genCode(ph);
                objCode.append("label" + QString::number(nl) + "\n");
                optCode.append("label" + QString::number(nl) + "\n");
            }

            if (phrase[i].expression[0].lexeme == "then")
            {
                QVector<Element>ph;
                int layer = phrase[i].layer;
                i++;
                while (i < n && phrase[i].layer > layer)
                {
                    ph.append(phrase[i]);
                    i++;
                }
                genCode(ph);
                objCode.append("\nlabel" + QString::number(nl) + ":\n");
                optCode.append("\nlabel" + QString::number(nl) + ":\n");
            }
            return;
        }
    }

}

void gen::result()
{
    for (QString & str: objCode)
    {
        code1->append(str);
    }
    for (QString & str: optCode)
    {
        code2->append(str);
    }
    emit genResult(*code1, *code2);
    code1->clear();
    code2->clear();
    objCode.clear();
    optCode.clear();
    replaceTable.clear();
    numLayout = 0;
}
