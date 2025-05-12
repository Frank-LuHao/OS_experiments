#ifndef MANAGER_H
#define MANAGER_H

#include "mcb.h"
#include "linklist.h"

// 内存管理器
typedef struct {
    LkList lkFreeList;         // 空闲分区表
    LkList lkAllocatedList;    // 已分配分区表
    int nTotalSize;            // 总内存大小(640KB)
} MemoryManager;


void init_memory(MemoryManager *manager, int total_size);  // 初始化内存管理器
int allocate_memory(MemoryManager *manager, int size, int id, int algorithm); // 分配内存, 0表示首次适应算法, 1表示最佳适应算法, 2表示最坏适应算法
int free_memory(MemoryManager *manager, int id);  // 释放内存
void display_memory(MemoryManager *manager);  // 显示内存状态

#endif