#ifndef LkList_H
#define LkList_H

#include "mcb.h"

#define LEN 128
#define DATA MemBlock

typedef struct
{
    DATA *data[LEN]; 
    int hh, tt;
} LkList;

void initLkList(LkList *q); // 初始化
int IsEmpty(LkList *q); // 判断是否为空
int IsFull(LkList *q); // 判断是否已满
int Size(LkList *q); // 返回链表大小
void Sort(LkList *q, int (*cmp)(const DATA *, const DATA *)); // 排序函数
DATA* get(LkList *q, int i); // 获取第i个元素
void delete(LkList *q, int i); // 删除第i个元素

// 模拟队列操作
void enqueue(LkList *q, DATA *item); // 入队
DATA* dequeue(LkList *q); // 出队

#endif