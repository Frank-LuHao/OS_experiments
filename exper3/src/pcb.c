#include<stdio.h>
#include "pcb.h"

void show(PCB * u)
{
    char c;
    if (u->nState) c = 'R';
    else c = 'W';

    printf("%5s   %5c   %5d   %5d   %5d\n", u->sName, c, u->nPriority, u->nArrivalTime, u->nBurstTime);
}