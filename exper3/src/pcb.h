// pcb块设计
#ifndef PCB_H
#define PCB_H

typedef struct
{
    int nId; // PCB的ID
    char sName[20]; // PCB的名称
    int nState; // PCB的状态, 0表示就绪，1表示运行
    int nArrivalTime; // PCB到达时间
    int nPriority; // PCB的优先级, 0表示最高优先级
    int nBurstTime; // PCB的服务时间
} PCB;

void show(PCB *); //输出显示

#endif