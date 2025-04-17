#include <stdio.h>
#include <stdlib.h>
#include "pcb.h"
#include "linklist.h"

void initLkList(LkList *q)
{
    q->hh = 0;
    q->tt = -1;
}

int IsEmpty(LkList *q)
{
    if (q->hh > q->tt)
    {
        return 1; // 队列为空
    }
    return 0; // 队列不为空
}

int IsFull(LkList *q)
{
    if (q->tt == LEN - 1)
    {
        return 1; // 队列已满
    }
    return 0; // 队列不满
}

int Size(LkList *q)
{
    return q->tt - q->hh + 1; // 返回队列大小
}

void enqueue(LkList *q, PCB *item)
{
    if (IsFull(q))
    {
        printf("LkList is full\n");
        return;
    }
    item->nState = 0;
    q->data[++(q->tt)] = item;
}

PCB* dequeue(LkList *q)
{
    if (IsEmpty(q))
    {
        printf("LkList is empty\n");
        return NULL;
    }
    q->data[(q->hh)]->nState = 1;
    return q->data[(q->hh)++];
}

void sort(LkList *q, int (*cmp)(const PCB *, const PCB *))
{
    for (int i = q->hh; i <= q->tt; i++)
    {
        for (int j = i + 1; j <= q->tt; j++)
        {
            if (cmp(q->data[i], q->data[j]) > 0)
            {
                PCB *temp = q->data[i];
                q->data[i] = q->data[j];
                q->data[j] = temp;
            }
        }
    }
}

void list(LkList *q, int time)
{
    printf("qname   state   nice    arritime   ndtime\n");
    
    for (int i = q->hh; i <= q->tt; i++)
        if (q->data[i]->nArrivalTime <= time)
            show(q->data[i]); 
    
    printf("\n");
}

PCB* get(LkList *q, int i)
{
    if (i <= 0 || i > Size(q))
    {
        printf("Index out of range  %d \n", i);
        return NULL;
    }
    return q->data[q->hh + i - 1];
}

void delete(LkList *q, int i)
{
    if (i <= 0 || i > Size(q))
    {
        printf("Index out of range  %d \n", i);
        return;
    }
    for (int j = q->hh + i - 1; j < q->tt; j++)
    {
        q->data[j] = q->data[j + 1];
    }
    q->tt--;
}