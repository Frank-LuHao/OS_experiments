#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void initQueue(Queue *q)
{
    q->hh = 0;
    q->tt = -1;
}

int IsEmpty(Queue *q)
{
    if (q->hh > q->tt)
    {
        return 1; // 队列为空
    }
    return 0; // 队列不为空
}

int IsFull(Queue *q)
{
    if (q->tt == LEN - 1)
    {
        return 1; // 队列已满
    }
    return 0; // 队列不满
}

int Size(Queue *q)
{
    return q->tt - q->hh + 1; // 返回队列大小
}

void enqueue(Queue *q, PCB *item)
{
    if (IsFull(q))
    {
        printf("Queue is full\n");
        return;
    }
    item->nState = 0;
    q->data[++(q->tt)] = item;
}

PCB* dequeue(Queue *q)
{
    if (IsEmpty(q))
    {
        printf("Queue is empty\n");
        return NULL;
    }
    q->data[(q->hh)]->nState = 1;
    return q->data[(q->hh)++];
}

void sort(Queue *q, int (*cmp)(const PCB *, const PCB *))
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
