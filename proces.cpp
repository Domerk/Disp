#include "proces.h"

Proces::Proces(char NName, int NDur, int NAct)
{

   PrName = NName;
   PrTmDur = NDur;
   PrTmAct = NAct;
   TActDur = NAct;
   PrActive = false;

}

void Proces::show(QPainter *painter)
{

}

Proces::~Proces()
{

}
