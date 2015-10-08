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
                QString errorTxt;
                errorTxt.append(tr("Строка c ошибкой: "));

                for (Lexeme & lx : Str)
                {
                    errorTxt.append(lx.lexeme);
                    errorTxt.append(" ");
                }

                emit parsError(errorTxt);
                break;
            }
        }
    }

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
    else
    {
        return false;
    }

}

bool parser::thisIsF(QVector<Lexeme> F)
{
    /* Выражение является F, если удовляетворяет условию:
       if E then T else F | if E then F | a := a        */

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

             }
             else
             {
                 return false;
             }
         }

     }
     else
     {
        return false;
     }

}

bool parser::thisIsT(QVector<Lexeme> T)
{
    /* Выражение является T, если удовлетворяет условию
       if E then T else T | a := a  */

    bool u1 = false; // для проверки, что if - then - else
    bool u2 = false; // для проверки, что E
    bool u3 = false; // для проверки, что Т

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
                while (T[i].lexeme != "then" && i<n)
                {
                    forE.append(T[i]);
                    i++;
                }
                u2 = thisIsE(forE);

            }
            else
            {
                return false;
            }
        }

    }
    else
    {
       return false;
    }

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
    else
    {
        return false;
    }

}









