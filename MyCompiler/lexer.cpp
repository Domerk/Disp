#include "lexer.h"

lexer::lexer(QObject *parent)
    : QObject(parent)
{

    keyword = new QRegularExpression("\\b(if|then|else)\\b"); // ключевые слова
    number = new QRegularExpression("\\bM{0,4}(CM|CD|D?C{0,3})(XC|XL|L?X{0,3})(IX|IV|V?I{0,3})\\b"); // латинские цифры
    identifier = new QRegularExpression("\\b([a-zA-Z]+\\w*)+\\b"); // идентификаторы
    comparisonSign = new QRegularExpression("\\b(<|>|=)\\b"); // знаки сравнения


}

void lexer::textSlot (QString newText)
{
    text = newText;
    text = text.simplified(); // удаляем пробелы в начале и в конце строки, а так же заменяем двойные пробелы одиночными

    lexTable.clear();
    thisIsFail.clear();

    analyze();
}

void lexer::analyze()
{
    // разделим исходную строку на подстроки
    QStringList qsl = text.split(QRegularExpression("\\b"));
    bool isComment = false;

    // проанализируем подстроки на предмет того, являются ли они лексемами
    for (QString & newLex : qsl)
    {

        if (isComment && newLex != "*/")
        {
            continue;
        }
        else
        {
            isComment = false;
            continue;
        }

        if (newLex == "/*")
        {
            isComment = true;
            continue;
        }

        newLex = newLex.trimmed();
        if (!newLex.isEmpty())
        {
            // тут будет всякий код

            if (newLex == ":=")
            {
                Lexeme lex;
                lex.lexeme = newLex;
                lex.type = "Assignment";
                lexTable.append(lex);
                continue;
            }

            QRegularExpressionMatch match = keyword->match(newLex);
            if (match.hasMatch())
            {
                Lexeme lex;
                lex.lexeme = newLex;
                lex.type = "Keyword";
                lexTable.append(lex);
                continue;
            }

            match = number->match(newLex);
            if (match.hasMatch())
            {
                Lexeme lex;
                lex.lexeme = newLex;
                lex.type = "Number";
                lexTable.append(lex);
                continue;
            }

            match = identifier->match(newLex);
            if (match.hasMatch())
            {
                Lexeme lex;
                lex.lexeme = newLex;
                lex.type = "Identifier";
                lexTable.append(lex);
                continue;
            }

            match = comparisonSign->match(newLex);
            if (match.hasMatch())
            {
                Lexeme lex;
                lex.lexeme = newLex;
                lex.type = "Comparison Sign";
                lexTable.append(lex);
                continue;
            }



        }
    }

}

void lexer::result()
{
    QString rpt;
    rpt.append(tr("<table border=1><tr><td>Лексема</td><td>Тип лексемы</td></tr>"));

    for (Lexeme & newLex : lexTable)
    {
        rpt.append("<tr><td>");
        rpt.append(newLex.lexeme);
        rpt.append("</td><td>");
        rpt.append(newLex.type);
        rpt.append("</td></tr>");
    }
    rpt.append("</table>");

    emit tableSignal(rpt);

}

lexer::~lexer()
{

    delete keyword;
    delete number;
    delete identifier;
    delete comparisonSign;

}

