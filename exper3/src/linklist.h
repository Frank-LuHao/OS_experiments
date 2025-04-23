#ifndef LkList_H
#define LkList_H

#define LEN 128
#include "pcb.h"

typedef struct
{
    PCB *data[LEN]; // 数据域
    int hh, tt; // 队头指针
} LkList;

void initLkList(LkList *q); // 初始化
int IsEmpty(LkList *q); // 判断是否为空
int IsFull(LkList *q); // 判断是否已满
int Size(LkList *q); // 返回链表大小
void sort(LkList *q, int (*cmp)(const PCB *, const PCB *)); // 排序函数
void list(LkList *q, int time); // 输出显示
PCB* get(LkList *q, int i); // 获取第i个元素
void delete(LkList *q, int i); // 删除第i个元素

// 模拟队列操作
void enqueue(LkList *q, PCB *item); // 入队
PCB* dequeue(LkList *q); // 出队

#endif