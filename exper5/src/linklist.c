#include <stdio.h>
#include <stdlib.h>
#include "mcb.h"
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

void enqueue(LkList *q, DATA *item)
{
    if (IsFull(q))
    {
        printf("LkList is full\n");
        return;
    }
    q->data[++(q->tt)] = item;
}

DATA* dequeue(LkList *q)
{
    if (IsEmpty(q))
    {
        printf("LkList is empty\n");
        return NULL;
    }
    return q->data[(q->hh)++];
}

void Sort(LkList *q, int (*cmp)(const DATA *, const DATA *))
{
    for (int i = q->hh; i <= q->tt; i++)
    {
        for (int j = i + 1; j <= q->tt; j++)
        {
            if (cmp(q->data[i], q->data[j]) > 0)
            {
                DATA *temp = q->data[i];
                q->data[i] = q->data[j];
                q->data[j] = temp;
            }
        }
    }
}

DATA* get(LkList *q, int i)
{
    if (i < 0 || i >= Size(q))
    {
        printf("Index out of range  %d \n", i);
        return NULL;
    }
    return q->data[q->hh + i];
}

void delete(LkList *q, int i)
{
    if (i < 0 || i >= Size(q))
    {
        printf("Index out of range  %d \n", i);
        return;
    }
    for (int j = q->hh + i; j < q->tt; j++)
    {
        q->data[j] = q->data[j + 1];
    }
    q->tt--;
}