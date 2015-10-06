#include "parser.h"

parser::parser(QObject *parent)
    : QObject(parent)
{

}

parser::~parser()
{

}

void parser::lexTableSlot(QVector tl)
{
    lexTable = tl;
}
