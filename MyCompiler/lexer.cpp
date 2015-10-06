#include "lexer.h"

lexer::lexer(QObject *parent)
    : QObject(parent)
{
    keyword = new QRegularExpression("^(if|then|else)$"); // ключевые слова
    number = new QRegularExpression("^M{0,4}(CM|CD|D?C{0,3})(XC|XL|L?X{0,3})(IX|IV|V?I{0,3})$"); // латинские цифры
    identifier = new QRegularExpression("^([a-zA-Z]+\\w*)+$"); // идентификаторы
    comparisonSign = new QRegularExpression("^(<|>|=)$"); // знаки сравнения
}

void lexer::textSlot (QString newText)
{
    text = newText;
    textCopy = newText; // создаём копию текста на тот случай, если придётся выделять в нём ошибки
    text = text.simplified(); // удаляем пробелы в начале и в конце строки, а так же заменяем двойные пробелы одиночными

    lexTable.clear(); // очищаем таблицу лексем
    thisIsFail.clear(); // очищаем вектор ошибок

    analyze(); // вызываем анализатор
    result(); // формируем и возвращаем результат
}

void lexer::addLexToTable(QString nLex, QString nType)
{
    Lexeme lex; // создаём новую перемнную типа Лексема
    lex.lexeme = nLex; // задаём имя
    lex.type = nType; // задаём тип
    lexTable.append(lex); // добавляем в конец таблицы
}

void lexer::analyze()
{
    // разделим исходную строку на подстроки
    // получаем список строк, каждая из которых - слово
    // параметр QString::SkipEmptyParts запрещает создание пустых строк
    QStringList qsl = text.split(QRegularExpression("(\\b|\\s)"), QString::SkipEmptyParts);
    bool isComment = false; // флаг налиячия комментария - не комментарий

    // проанализируем подстроки на предмет того, являются ли они лексемами
    for (QString & newLex : qsl)
    {
        newLex = newLex.trimmed(); // обрезаем лишние пробелы
        if (!newLex.isEmpty()) // если строка не пустая, её можно анализировать
        {
            if (isComment && newLex != "*/") // если комментарий и он не закончен
                continue; // к следующему шагу

            if (newLex == "*/") // если конец комментария
            {
                isComment = false; // сбрасываем флаг
                continue; // к следующему шагу
            }

            if (newLex == "/*") // если начался комментарий
            {
                isComment = true; // ставим флаг
                continue;
            }

            if (newLex == ":=")
            {
                addLexToTable(newLex, "Assignment");
                continue;
            }

            if (newLex == ";")
            {
                addLexToTable(newLex, "Separator");
                continue;
            }

            // Далее сравниваем строку с реулярными выражениями для лексем
            QRegularExpressionMatch match = keyword->match(newLex);
            if (match.hasMatch())
            {
                addLexToTable(newLex, "Keyword");
                continue;
            }

            match = number->match(newLex);
            if (match.hasMatch())
            {
                addLexToTable(newLex, "Number");
                continue;
            }

            match = identifier->match(newLex);
            if (match.hasMatch())
            {
                addLexToTable(newLex, "Identifier");
                continue;
            }

            match = comparisonSign->match(newLex);
            if (match.hasMatch())
            {
                addLexToTable(newLex, "Comparison Sign");
                continue;
            }

            // если дошли до этого места, то считанная строка содержит не лексему
            // проверяем, есть ли такая ошибочная строка в векторе ошибок
            bool thisFailExist = false;
            if (!thisIsFail.empty())
            {
                for (QString & fail : thisIsFail)
                {
                    if (fail == newLex)
                    {
                        thisFailExist = true;
                    }
                }
            }
            // Если не встречалась - добавляем её в вектор, иначе не делаем ничего
            if (!thisFailExist)
            {
                thisIsFail.append(newLex);
            }

        }
    }

}

void lexer::result()
{
    QString rpt; // формируем строку - таблицу лексем
    rpt.append(tr("<table border=1 width='200' align='center' cellpadding=5><tr><td><b>Лексема</b></td><td><b>Тип лексемы</b></td></tr>"));

    for (Lexeme & newLex : lexTable)
    {
        rpt.append("<tr><td>");

        if (newLex.lexeme == "<") // заменяем знак его html-представлением
            rpt.append("&lt;"); // да, это тоже фикс
        else
            rpt.append(newLex.lexeme);

        rpt.append("</td><td>");
        rpt.append(newLex.type);
        rpt.append("</td></tr>");
    }
    rpt.append("</table>");

    emit tableSignal(rpt); // отправляем полученную строку

    // если в ходе лексического анализа возникли ошибки
    if (!thisIsFail.empty())
    {
        QString correctText = textCopy; // берём исходный текст
        QString newStr;

        correctText.replace("<", "&lt;"); // заменяем < и > на их представления
        correctText.replace(">", "&gt;");

        // заменяем ошибочные подстроки такими же подстроками, но в тегах цвета
        for (QString & oldStr : thisIsFail)
        {
            newStr.append("<b><FONT COLOR=RED>");
            newStr.append(oldStr);
            newStr.append("</FONT></b>");
            correctText.replace(oldStr, newStr);
        }

        correctText.replace("\n", "<br>"); // заменяем обычный перенос строки html-переносом
        emit failSignal(correctText); // отправляем
    }
    else
    {
        // если лексических ошибок нет, можно передать инфу синтаксическому анализатору
        emit lexTableSignal(lexTable);
    }

}

lexer::~lexer()
{
    delete keyword;
    delete number;
    delete identifier;
    delete comparisonSign;
}

