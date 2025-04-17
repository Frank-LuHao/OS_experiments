#ifndef QUEUE_H
#define QUEUE_H

#define LEN 128
#include "pcb.h"

typedef struct
{
    PCB *data[LEN]; // 数据域
    int hh, tt; // 队头指针
} Queue;

void initQueue(Queue *q); // 初始化队列
int IsEmpty(Queue *q); // 判断队列是否为空
int IsFull(Queue *q); // 判断队列是否已满
int Size(Queue *q); // 返回队列大小
void enqueue(Queue *q, PCB *item); // 插入函数
PCB* dequeue(Queue *q); // 删除函数
void sort(Queue *q, int (*cmp)(const PCB *, const PCB *)); // 排序函数

#endif