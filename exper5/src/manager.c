#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#include"manager.h"

// 初始化内存管理器
void init_memory(MemoryManager *manager, int total_size)
{
    manager->nTotalSize = total_size; // 设置总内存大小
    initLkList(&manager->lkFreeList); // 初始化空闲分区表
    initLkList(&manager->lkAllocatedList); // 初始化已分配分区表

    // 创建一个初始的空闲内存块
    MemBlock *initial_block = (MemBlock *)malloc(sizeof(MemBlock));
    initial_block->nId = 0; // ID为0表示初始块
    initial_block->nStartLoc = 0; // 起始地址为0
    initial_block->nSize = total_size; // 大小为总内存大小

    enqueue(&manager->lkFreeList, initial_block); // 将初始块加入空闲分区表
}  

// 分配内存
int allocate_memory(MemoryManager *manager, int nSize, int id, int algorithm)
{
    if (nSize <= 0 || nSize > manager->nTotalSize) 
    {
        return -1; // 无效的内存请求
    }
    MemBlock *allocated_block = NULL; // 分配的内存块

    if (algorithm == 0) // 首次适应算法
    {
        for (int i = 0; i < Size(&manager->lkFreeList); i++) 
        {
            MemBlock *block = get(&manager->lkFreeList, i);
            if (block->nSize >= nSize) 
            {
                allocated_block = block; // 找到合适的空闲块
                break;
            }
        }
    } 
    else if (algorithm == 1) // 最佳适应算法
    {
        int best_index = -1;
        int best_size = manager->nTotalSize + 1; // 初始化为一个较大的值

        for (int i = 0; i < Size(&manager->lkFreeList); i++) 
        {
            MemBlock *block = get(&manager->lkFreeList, i);
            if (block->nSize >= nSize && block->nSize < best_size) 
            {
                best_size = block->nSize;
                best_index = i; // 找到最佳适应块
            }
        }

        if (best_index != -1) 
        {
            allocated_block = get(&manager->lkFreeList, best_index);
        }
    } 
    else if (algorithm == 2) // 最坏适应算法
    {
        int worst_index = -1;
        int worst_size = -1;

        for (int i = 0; i < Size(&manager->lkFreeList); i++) 
        {
            MemBlock *block = get(&manager->lkFreeList, i);
            if (block->nSize >= nSize && block->nSize > worst_size) 
            {
                worst_size = block->nSize;
                worst_index = i; // 找到最坏适应块
            }
        }

        if (worst_index != -1) 
        {
            allocated_block = get(&manager->lkFreeList, worst_index);
        }
    }

    if (allocated_block == NULL) 
    {
        return -1; // 没有足够的内存可供分配
    }
    else
    {
        // 创建一个新的内存块
        MemBlock *new_block = (MemBlock *)malloc(sizeof(MemBlock));
        new_block->nId = id; // 设置ID
        new_block->nStartLoc = allocated_block->nStartLoc; // 设置起始地址
        new_block->nSize = nSize; // 设置大小

        // 更新空闲分区表
        allocated_block->nStartLoc += nSize; // 更新起始地址
        allocated_block->nSize -= nSize; // 更新大小

        enqueue(&manager->lkAllocatedList, new_block); // 将新块加入已分配分区表

        return new_block->nStartLoc; // 返回分配的内存块的起始地址
    }
}

// 释放内存
int free_memory(MemoryManager *manager, int id)  
{
    // 遍历已分配分区表，找到对应的内存块
    bool found = false;

    for (int i = 0; i < Size(&manager->lkAllocatedList); i++) 
    {
        MemBlock *block = get(&manager->lkAllocatedList, i);
        if (block->nId == id) 
        {
            // 找到对应的内存块，释放它
            enqueue(&manager->lkFreeList, block); // 将其加入空闲分区表
            delete(&manager->lkAllocatedList, i); // 从已分配分区表中删除
            found = true;
        }
    }

    Sort(&manager->lkFreeList, cmp); // 按照起始地址从小到大排序空闲分区表

    // 合并算法
    if (found) 
    {
        // 合并相邻的空闲内存块
        for (int i = 0; i < Size(&manager->lkFreeList); i++) 
        {
            MemBlock *block = get(&manager->lkFreeList, i);
            if (block->nId == id) 
            {
                // 考虑前后相邻的空闲块
                MemBlock *prev_block = (i > 0) ? get(&manager->lkFreeList, i - 1) : NULL;
                MemBlock *next_block = (i < Size(&manager->lkFreeList) - 1) ? get(&manager->lkFreeList, i + 1) : NULL;
                if (prev_block && prev_block->nStartLoc + prev_block->nSize == block->nStartLoc) 
                {
                    if (next_block && block->nStartLoc + block->nSize == next_block->nStartLoc) 
                    {
                        // 合并前后三个块
                        prev_block->nSize += block->nSize + next_block->nSize;
                        delete(&manager->lkFreeList, i + 1);
                        delete(&manager->lkFreeList, i);      //注意此处先后顺序，先i+1后i
                        free(block); // 释放当前块
                        free(next_block); // 释放下一个块
                    }
                    else 
                    {
                        // 合并前一个空闲块
                        prev_block->nSize += block->nSize;
                        free(block); // 释放当前块
                        delete(&manager->lkFreeList, i);
                    }
                }
                else  
                {
                    if (next_block && block->nStartLoc + block->nSize == next_block->nStartLoc) 
                    {
                        // 合并后一个空闲块
                        block->nSize += next_block->nSize;
                        free(next_block); // 释放下一个块
                        delete(&manager->lkFreeList, i + 1);
                    }
                }

                break;
            }
        }        

        return 0; // 成功释放内存
    }
    else
    {
        return -1; // 未找到对应的内存块
    }
}

// 显示内存状态
void display_memory(MemoryManager *manager)
{
    // 显示空闲分区表
    printf("**********Unallocated Table**********\n");
    printf("%-10s%-10s%-10s%-10s\n", "index", "Start", "End", "Size");
    for (int i = 0; i < Size(&manager->lkFreeList); i++) 
    {
        MemBlock *block = get(&manager->lkFreeList, i);
        printf("%-10d%-10d%-10d%-10d\n", block->nId, block->nStartLoc, block->nStartLoc + block->nSize, block->nSize);    
    }

    puts("");

    // 显示已分配分区表
    printf("**********Allocated Table**********\n");
    printf("%-10s%-10s%-10s%-10s\n", "index", "Start", "End", "Size");
    for (int i = 0; i < Size(&manager->lkAllocatedList); i++) 
    {
        MemBlock *block = get(&manager->lkAllocatedList, i);
        printf("%-10d%-10d%-10d%-10d\n", block->nId, block->nStartLoc, block->nStartLoc + block->nSize, block->nSize);
    }
    
    puts("");
    printf("====================================\n");
}