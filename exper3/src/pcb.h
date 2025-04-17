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

// int remaining_time; // PCB剩余服务时间
// int waiting_time; // PCB等待时间
// int turnaround_time; // PCB周转时间

#endif