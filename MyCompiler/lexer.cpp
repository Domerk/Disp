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
    textCopy = newText;
    text = text.simplified(); // удаляем пробелы в начале и в конце строки, а так же заменяем двойные пробелы одиночными

    lexTable.clear();
    thisIsFail.clear();

    analyze();
    result();
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

            if (!thisFailExist)
            {
                thisIsFail.append(newLex);
            }

        }
    }

}

void lexer::result()
{
    QString rpt;
    rpt.append(tr("<table border=1 width='200' align='center' cellpadding=5><tr><td><b>Лексема</b></td><td><b>Тип лексемы</b></td></tr>"));

    for (Lexeme & newLex : lexTable)
    {
        rpt.append("<tr><td>");

        if (newLex.lexeme == "<")
            rpt.append("&lt;");
        else
            rpt.append(newLex.lexeme);

        rpt.append("</td><td>");
        rpt.append(newLex.type);
        rpt.append("</td></tr>");
    }
    rpt.append("</table>");

    emit tableSignal(rpt);

    // если в ходе лексического анализа возникли ошибки
    if (!thisIsFail.empty())
    {
        QString correctText = textCopy;
        QString newStr;

        correctText.replace("<", "&lt;");
        correctText.replace(">", "&gt;");

        for (QString & oldStr : thisIsFail)
        {
            newStr.append("<b><FONT COLOR=RED>");
            newStr.append(oldStr);
            newStr.append("</FONT></b>");
            correctText.replace(oldStr, newStr);
        }

        correctText.replace("\n", "<br>");
        emit failSignal(correctText);
    }

}

lexer::~lexer()
{

    delete keyword;
    delete number;
    delete identifier;
    delete comparisonSign;

}

