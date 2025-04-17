// 高响应比优先调度算法
#include <stdio.h>
#include <stdlib.h>
#include "src/queue.h"

int nTime = 0; // 当前时间

int cmp(const PCB *a, const PCB *b)
{
    double responseRatioA = (nTime - a->nArrivalTime + a->nBurstTime) / (double)a->nBurstTime;
    double responseRatioB = (nTime - b->nArrivalTime + b->nBurstTime) / (double)b->nBurstTime;
    return responseRatioB - responseRatioA; 
}

int main()
{
    int nNumProcesses = 0; // 进程数
    Queue ReadyQueue; // 就绪队列
    initQueue(&ReadyQueue); // 初始化就绪队列

    printf("--------------HRRN调度算法-------------\n");
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

    //输出就绪队列
    while (!IsEmpty(&ReadyQueue))
    {
        sort(&ReadyQueue, cmp); // 排序

        int t = Size(&ReadyQueue);
        int minArrivalTime = 0x3f3f3f3f;
        PCB *p = dequeue(&ReadyQueue);
        while (p->nArrivalTime > nTime && t--) // 等待进程到达
        {
            if (p->nArrivalTime < minArrivalTime) // 找到最小到达时间
            {
                minArrivalTime = p->nArrivalTime;
            }
            enqueue(&ReadyQueue, p); // 将进程重新加入队列
            p = dequeue(&ReadyQueue); // 取出下一个进程
        }

        if (p->nArrivalTime > nTime) // 如果没有进程到达
        {
            enqueue(&ReadyQueue, p);
            printf("当前时间 %d --- 等待进程到达\n", nTime);
            nTime = minArrivalTime; // 更新当前时间
        }
        else
        {
            printf("当前时间 %d --- 开始执行进程 %s\n", nTime, p->sName);
            nTime += p->nBurstTime; // 更新当前时间
            printf("当前时间: %d --- 进程 %d 执行完毕\n", nTime, p->nId);
            free(p);
        }
    }

    return 0;
}