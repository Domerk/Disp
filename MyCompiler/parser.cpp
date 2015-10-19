#include "parser.h"

parser::parser(QObject *parent)
    : QObject(parent)
{

}

parser::~parser()
{

}

void parser::lexTableSlot(QVector<Lexeme> tl)
{
    lexTable = tl; // Получаем таблицу лексем
}

void parser::startParser()
{
    if (!lexTable.isEmpty())
    {
        analize();
        result();
        emit treeSignal(tree);
        tree.clear();
    }
    else
    {
        emit parsError(tr("Отсутсвуют данные лексического анализа!"));
    }
}

void parser::analize()
{
    QVector <Lexeme> Str;
    QString errorTxt; // Строка с сообщением об ошибке
    bool separatorExist = false; // Наличие разделителя

    for (Lexeme & newLex : lexTable)
    {
        Str.append(newLex); // Добавляем в вектор лексему
        if (newLex.type == "Separator") // Если это разделитель
        {
            separatorExist = true; // Поднимаем флаг

            // Проверям, является ли строка синтаксически правильной
            if (thisIsS(Str) == true)
            {
                QVector<Lexeme> vct;
                vct.append(newLex);
                addInTree(vct, "S", true, 0, 0);
                Str.clear(); // Если всё хорошо, чистим её
            }
            else
            {
                if (errorTxt.isEmpty()) // иначе если список ошибок пуст
                    errorTxt.append(tr("Список ошибок: <br>"));
                else
                    errorTxt.append("<br>"); // иначе просто добавляем перенос

                for (Lexeme & lx : Str) // Для всех лексем в ошибочной строке
                {
                    if (lx.lexeme == "<") // Заменяем < на тег
                    {
                        errorTxt.append("&lt;");
                    }
                    else
                    {
                        if(lx.lexeme == ">") // Заменяем > на тег
                            errorTxt.append("&gt;");
                        else
                            errorTxt.append(lx.lexeme); // Добавляем лексему
                    }
                    errorTxt.append(" "); // Добавляем пробел
                }

                Str.clear(); // Очищаем строку
            }
        }
    }
    if (!separatorExist) // Если нет ;, то сообщаем об этом
        errorTxt.append(tr("Отсутсвует ';' !"));

    if (!errorTxt.isEmpty()) // Если есть сообщение об ошибке
        emit parsError(errorTxt); // То оправляем его
}

// ========================================================

bool parser::thisIsS(QVector<Lexeme> S)
{
    // Выражение является S, если состоит из F и Separator
    int n = S.size();
    if (n > 3 && S[n-1].type == "Separator")
    {
        S.resize(n-1);
        int layer = 0;
        return thisIsF(S, layer);
    }
    return false;
}

// ========================================================

bool parser::thisIsF(QVector<Lexeme> F, int layer)
{
    /* Выражение является F, если удовляетворяет условию:
       if E then T else F | if E then F | a := a        */

    bool u1 = false;
    bool u2 = false;
    bool u3 = false;

    QVector <Lexeme> forE;
    QVector <Lexeme> forT;
    QVector <Lexeme> forF;

    int n = F.size();
    if (n > 2) // Если в строке есть не менее 3 элементов
    {
        if (n == 3) // Если элемента всего 3, то это строка a := a
        {
            // Проверяем, так ли это, и возвращаем результат
            bool result = (F[0].type == "Identifier" && F[1].type == "Assignment" && (F[2].type == "Identifier" || F[2].type == "Number"));

            if (result)
            {
                addInTree(F, "F", true, layer, 3);
            }
            return result;

        }
        else
        {
            if (F[0].lexeme == "if") // Иначе есть первая лексема - if
            {
                QVector <Lexeme> vct;
                vct.append(F[0]);
                addInTree(vct, "F", false, layer, 0);
                vct.clear();

                int i = 1;
                int f = 1;
                while (i<n && F[i].lexeme != "then") // Пока не нашли then или недошли до конца
                {
                    forE.append(F[i]); // Заносим элементы в подстроку
                    i++;
                }

                u1 = thisIsE(forE, layer+1); // Отправляем её на проверку и сохраняем результат

                vct.append(F[i]);
                addInTree(vct, "F", false, layer, 0);
                vct.clear();

                // далее необходимо определить, есть ли у нас else

                i++;

                while (i<n && f!=0) // Пока не дошли до конца или не нашли нужный else
                {
                    if(F[i].lexeme == "if")
                        f++; // Увеличиваем флаг

                    if(F[i].lexeme == "else")
                        f--;

                    if (f != 0)
                        forT.append(F[i]); // Заносим элементы в подстроку

                    i++;
                }

                // если f = 0, значит, мы не дошли до конца вектора
                // но при этом нашли else
                if (f == 0)
                {
                    u2 = thisIsT(forT, layer+1); // Формируем последнюю часть строки

                    vct.append(F[i-1]);
                    addInTree(vct, "F", false, layer, 1);
                    vct.clear();
                    fixNumInTree(layer, 1);

                    while (i<n)
                    {
                        forF.append(F[i]);
                        i++;
                    }
                    u3 = thisIsF(forF, layer+1); // Отправляем на проверку

                    return (u1 && u2 && u3); // Возвращаем результат
                }
                else
                {
                    fixNumInTree(layer, 2);
                    u2 = thisIsF(forT, layer+1); // Иначе считаем, что if E then F
                    return (u1 && u2); // Возвращаем результат
                }
            }
        }
    }
    return false;
}

// ========================================================

bool parser::thisIsT(QVector<Lexeme> T, int layer)
{
    /* Выражение является T, если удовлетворяет условию
       if E then T else T | a := a  */

    bool u1 = false;
    bool u2 = false;
    bool u3 = false;

    QVector <Lexeme> forE;
    QVector <Lexeme> forT1;
    QVector <Lexeme> forT2;

    // результат = u1 && u2 && u3

    int n = T.size();
    if (n > 2)
    {
        if (n == 3)
        {
            bool result = (T[0].type == "Identifier" && T[1].type == "Assignment" && (T[2].type == "Identifier" || T[2].type == "Number"));

            if (result)
            {
                addInTree(T, "T", true, layer, 5);
            }
            return result;
        }
        else
        {
            if (T[0].lexeme == "if")
            {
                QVector<Lexeme> vct;
                vct.append(T[0]);
                addInTree(vct, "T", false, layer, 4);
                vct.clear();

                int i = 1;
                int f = 1;
                while (i<n && T[i].lexeme != "then")
                {
                    forE.append(T[i]);
                    i++;
                }

                u1 = thisIsE(forE, layer+1);

                vct.append(T[i]);
                addInTree(vct, "T", false, layer, 4);
                vct.clear();

                i++;

                while (i<n && f!=0)
                {
                    if(T[i].lexeme == "if")
                        f++;

                    if(T[i].lexeme == "else")
                        f--;

                    if (f != 0)
                        forT1.append(T[i]); // Заносим элементы в подстроку
                    i++;
                }
                u2 = thisIsT(forT1, layer+1);

                if (f == 0)
                {
                    vct.append(T[i-1]);
                    addInTree(vct, "T", false, layer, 4);
                    vct.clear();
                }

                while (i<n)
                {
                    forT2.append(T[i]);
                    i++;
                }
                u3 = thisIsT(forT2, layer+1);

                return (u1 && u2 && u3);
            }
        }
    }
    return false;
}

// ========================================================

bool parser::thisIsE(QVector<Lexeme> E, int layer)
{
    /* Выражение является Е, если удовлетворяет условию
     * a < a | a > a | a = a */

    int n = E.size();
    if (n == 3)
    {
        bool result = ((E[0].type == "Identifier" || E[0].type == "Number") && E[1].type == "Comparison Sign" && (E[2].type == "Identifier" || E[2].type == "Number"));
        if (result)
        {
            if (E[1].lexeme == "<")
                addInTree(E, "E", true, layer, 6);

            if (E[1].lexeme == ">")
                addInTree(E, "E", true, layer, 7);

            if (E[1].lexeme == "=")
                addInTree(E, "E", true, layer, 8);
        }
        return result;
    }
    return false;
}

// ========================================================

void parser::result()
{
    QString res;
    if (!tree.isEmpty())
    {
        res.append(tr("<table border = 1 cellpadding=5><tr><td><b>Уровень</b></td><td><b>Выражение</b></td><td><b>Правило</b></td><td><b>Номер</b></td></tr>"));
        for (Element & elem : tree)
        {
            if (elem.num != 0)
            {
                res.append("<tr><td>");
                res.append(QString::number(elem.layer));
                res.append("</td><td>");

                for (Lexeme & lex : elem.expression)
                {
                    if (lex.lexeme == "<") // Заменяем < на тег
                    {
                        res.append("&lt;");
                    }
                    else
                    {
                        if(lex.lexeme == ">") // Заменяем > на тег
                            res.append("&gt;");
                        else
                            res.append(lex.lexeme); // Добавляем лексему
                    }

                    res.append(" ");
                }

                res.append("</td><td>");
                res.append(elem.type);
                res.append("</td><td>");
                res.append(QString::number(elem.num));
                res.append("</td></tr>");
            }

        }
        emit parsResult(res);
    }
}

// ========================================================

void parser::addInTree(QVector <Lexeme> elem, QString type, bool term, int layer, int n)
{
    Element newElem;
    newElem.expression = elem;
    newElem.layer = layer;
    newElem.terminate = term;
    newElem.type = type;
    newElem.num = n;
    tree.append(newElem);
}


void parser::fixNumInTree(int layer, int num)
{
    int n = tree.size() - 1;
    int f = 0;
    while (f < 2 && n >= 0)
    {
        if (tree[n].layer == layer && tree[n].num == 0)
        {
            tree[n].num = num;
            f++;
        }
        n--;
    }
}

