// 先来先服务算法
#include <stdio.h>
#include <stdlib.h>
#include "src/queue.h"

int cmp(const PCB *a, const PCB *b)
{
    return a->nArrivalTime - b->nArrivalTime; // 按到达时间升序排列
}

int main()
{
    int nNumProcesses = 0; // 进程数
    int nTime = 0; // 当前时间
    Queue ReadyQueue; // 就绪队列
    initQueue(&ReadyQueue); // 初始化就绪队列

    printf("--------------FCFS调度算法-------------\n");
    puts("");

    printf("请输入被调度进程数目：");
    scanf("%d", &nNumProcesses);
    puts("");

    
    for (int i = 0; i < nNumProcesses; i++)
    {
        PCB *p = (PCB *)malloc(sizeof(PCB)); // 动态分配内存
        
        printf("进程号NO.%d\n", i);
        p->nId = i;
        printf("请输入进程名：");
        scanf("%s", p->sName);
        printf("请输入进程到达时间:");
        scanf("%d", &p->nArrivalTime);
        printf("请输入进程运行时间：");
        scanf("%d", &p->nBurstTime);
        puts("");

        enqueue(&ReadyQueue, p); // 将进程加入就绪队列
    }

    sort(&ReadyQueue, cmp); // 排序

    //输出就绪队列
    while (!IsEmpty(&ReadyQueue))
    {
        PCB *p = dequeue(&ReadyQueue);
        printf("当前时间 %d --- 开始执行进程 %s\n", nTime, p->sName);
        nTime += p->nBurstTime; // 更新当前时间
        printf("当前时间: %d --- 进程 %d 执行完毕\n", nTime, p->nId);
        free(p); 
    }

    return 0;
}