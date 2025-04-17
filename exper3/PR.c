// 优先级调度算法
#include <stdio.h>
#include <stdlib.h>
#include "src/linklist.h"

int cmp(const PCB *a, const PCB *b)
{
    return a->nPriority - b->nPriority; // 按优先级升序排列
}

int main()
{
    int nNumProcesses = 0; // 进程数
    int nTime = 0; // 当前时间
    LkList ReadyLkList; // 就绪队列
    initLkList(&ReadyLkList); // 初始化就绪队列

    printf("--------------PR调度算法-------------\n");
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
        printf("请输入进程优先级:");
        scanf("%d", &p->nPriority);
        printf("请输入进程运行时间：");
        scanf("%d", &p->nBurstTime);
        puts("");

        enqueue(&ReadyLkList, p); // 将进程加入就绪队列
    }
    puts("");

    sort(&ReadyLkList, cmp); // 排序

    //输出就绪队列
    while (!IsEmpty(&ReadyLkList))
    {
        int minArrivalTime = 0x3f3f3f3f;
        PCB *p;
        for (int i = 1; i <= Size(&ReadyLkList); i++) // 等待进程到达
        {
            p = get(&ReadyLkList, i); // 获取队列中第i个元素
            if (p->nArrivalTime < minArrivalTime) // 找到最小到达时间
            {
                minArrivalTime = p->nArrivalTime;
            }
        }

        if (minArrivalTime > nTime) // 如果没有进程到达
        {
            printf("当前时间 %d\n*** 等待进程到达 ***\n", nTime);
            puts("");
            nTime = minArrivalTime; // 更新当前时间
        }
        else
        {
            int loc = 0;
            for (int i = 1; i <= Size(&ReadyLkList); i++) // 等待进程到达
            {
                p = get(&ReadyLkList, i);
                if (p->nArrivalTime <= nTime)
                {
                    loc = i;
                    break;
                }
            }

            p = get(&ReadyLkList, loc);
            delete(&ReadyLkList, loc);
            
            if (p == NULL)
            {
                printf("没有找到进程\n");
                break;
            }

            printf("当前时间 %d\n", nTime);

            printf("*** 正在运行进程 ***\n");
            printf("qname   state   nice    arritime   ndtime\n");
            show(p); 

            printf("*** 就绪队列状态 ***\n");
            list(&ReadyLkList, nTime); 

            nTime += p->nBurstTime; // 更新当前时间
            free(p); 
        }
    }

    return 0;
}