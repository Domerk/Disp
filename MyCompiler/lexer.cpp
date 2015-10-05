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

void lexer::addLexToTable(QString nLex, QString nType)
{
    Lexeme lex;
    lex.lexeme = nLex;
    lex.type = nType;
    lexTable.append(lex);
}

void lexer::analyze()
{
    // разделим исходную строку на подстроки
    QStringList qsl = text.split(QRegularExpression("\\b"), QString::SkipEmptyParts);
    bool isComment = false;

    // проанализируем подстроки на предмет того, являются ли они лексемами
    for (QString & newLex : qsl)
    {
        newLex = newLex.trimmed();
        if (!newLex.isEmpty())
        {
            if (isComment && newLex != "*/")
                continue;

            if (newLex == "*/")
            {
                isComment = false;
                continue;
            }

            if (newLex == "/*")
            {
                isComment = true;
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

            thisIsFail.append(newLex);

        }
    }

    result();

}

void lexer::result()
{
    QString rpt;
    rpt.append(tr("<table border=1 width='200' text align='center'><tr><td><b>Лексема</b></td><td><b>Тип лексемы</b></td></tr>"));

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

