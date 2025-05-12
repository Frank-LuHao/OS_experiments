#include"mcb.h"

int cmp(const MemBlock *a, const MemBlock *b) {
    return a->nStartLoc - b->nStartLoc;  // 按照起始地址升序排序
}