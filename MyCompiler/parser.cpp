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
    lexTable = tl;
}

void parser::startParser()
{
    if (!lexTable.isEmpty())
        analize();
    else
        emit parsError(tr("Отсутсвуют данные лексического анализа!"));
}

void parser::analize()
{
    QVector <Lexeme> Str;
    QString errorTxt;
    bool separatorExist = false;

    for (Lexeme & newLex : lexTable)
    {
        Str.append(newLex);
        if (newLex.type == "Separator")
        {
            separatorExist = true;

            if (thisIsS(Str) == true)
            {
                Str.clear();
            }
            else
            {
                if (errorTxt.isEmpty())
                    errorTxt.append(tr("Список ошибок: <br>"));
                else
                    errorTxt.append("<br>");

                for (Lexeme & lx : Str)
                {
                    if (lx.lexeme == "<")
                    {
                        errorTxt.append("&lt;");
                    }
                    else
                    {
                        if(lx.lexeme == ">")
                            errorTxt.append("&gt;");
                        else
                            errorTxt.append(lx.lexeme);
                    }
                    errorTxt.append(" ");
                }

                Str.clear();
            }
        }
    }

    if (!errorTxt.isEmpty())
        emit parsError(errorTxt);

    if (!separatorExist)
        emit parsError(tr("Отсутсвует ';' !"));
}


bool parser::thisIsS(QVector<Lexeme> S)
{
    // Выражение является S, если состоит из F и Separator
    int n = S.size();
    if (n > 3 && S[n-1].type == "Separator")
    {
        S.resize(n-1);
        return thisIsF(S);
    }

    return false;
}

bool parser::thisIsF(QVector<Lexeme> F)
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
    if (n > 2)
    {
        if (n == 3)
        {
            return (F[0].type == "Identifier" && F[1].type == "Assignment" && (F[2].type == "Identifier" || F[2].type == "Number"));
        }
        else
        {
            if (F[0].lexeme == "if")
            {
                int i = 1;
                int f = 1;
                while (i<n && F[i].lexeme != "then")
                {
                    forE.append(F[i]);
                    i++;
                }
                u1 = thisIsE(forE);

                // далее необходимо определить, есть ли у нас else

                i++;
                while (i<n && f!=0)
                {
                    forT.append(F[i]);

                    if(F[i].lexeme == "if")
                        f++;

                    if(F[i].lexeme == "else")
                        f--;

                    i++;
                }

                // если f = 0, значит, мы не дошли до конца вектора
                // но при этом нашли else
                if (f == 0)
                {
                    u2 = thisIsT(forT);
                    while (i<n)
                    {
                        forF.append(F[i]);
                        i++;
                    }
                    u3 = thisIsF(forF);

                    return (u1 && u2 && u3);
                }
                else
                {
                    u2 = thisIsF(forT);
                    return (u1 && u2);
                }
            }
        }

    }

    return false;

}

bool parser::thisIsT(QVector<Lexeme> T)
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
            return (T[0].type == "Identifier" && T[1].type == "Assignment" && (T[2].type == "Identifier" || T[2].type == "Number"));
        }
        else
        {
            if (T[0].lexeme == "if")
            {
                int i = 1;
                int f = 1;
                while (i<n && T[i].lexeme != "then")
                {
                    forE.append(T[i]);
                    i++;
                }
                u1 = thisIsE(forE);

                i++;
                while (i<n && f!=0)
                {
                    forT1.append(T[i]);
                    i++;

                    if(T[i].lexeme == "if")
                        f++;

                    if(T[i].lexeme == "else")
                        f--;
                }
                u2 = thisIsT(forT1);

                i++;
                while (i<n)
                {
                    forT2.append(T[i]);
                    i++;
                }
                u3 = thisIsT(forT2);

                return (u1 && u2 && u3);

            }
        }
    }
    return false;
}


bool parser::thisIsE(QVector<Lexeme> E)
{
    /* Выражение является Е, если удовлетворяет условию
     * a < a | a > a | a = a */

    int n = E.size();
    if (n == 3)
    {
        return ((E[0].type == "Identifier" || E[0].type == "Number") && E[1].type == "Comparison Sign" && (E[2].type == "Identifier" || E[2].type == "Number"));
    }

    return false;
}









