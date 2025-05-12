// mcb块设计
#ifndef MCB_H
#define MCB_H

// 内存块结构
typedef struct {
    int nId;             // 内存块ID
    int nStartLoc;       // 起始地址
    int nSize;           // 大小(KB)
} MemBlock;

int cmp(const MemBlock *a, const MemBlock *b);  // 排序函数

#endif