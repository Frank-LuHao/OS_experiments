#include <stdio.h>
#include <stdlib.h>

#define inf 0x3f3f3f3f
#define min(a, b) ((a) < (b) ? (a) : (b))

// 页表项结构
typedef struct {
    int nPageNum;    // 页号s
    int nLastUsed;     // LRU：记录最后访问时s间戳
    int nLoadedTime;   // FIFO：记录装入内存的时间
    int nNextUse;      // OPT：记录下次使用时间戳
} PCB;

int test_sequence[320];
PCB memory[33]; // 内存页号, 4 - 32 页

void init()
{
    // 初始化内存
    for (int i = 0; i < 33; i++)
    {
        memory[i].nPageNum = -1; // 页号
        memory[i].nLastUsed = -1; // LRU用：记录最后访问时间戳
        memory[i].nLoadedTime = -1; // FIFO用：记录装入内存的时间
        memory[i].nNextUse = -1; // OPT用：记录下次使用时间戳
    }
}

int InMemo(int page, int MemoSize)
{
    // 判断页是否在内存中
    for (int i = 0; i < MemoSize; i++)
    {
        if (memory[i].nPageNum == page)
        {
            return i;
        }
    }
    return -1;
}

float FIFO(int MemoSize)
{
    int PageHit = 0;   // 命中次数

    for (int i = 0; i < 320; i++)
    {
        int VisitPage = test_sequence[i];
        if (InMemo(VisitPage, MemoSize) != -1)
        { // 命中
            PageHit++;
        }
        else
        { // 缺页
            // 找到页框
            int nPageFrame = -1;
            int nLoadedTime = inf;
            for (int j = 0; j < MemoSize; j++)
            {
                if (memory[j].nPageNum == -1)
                { // 找到空页框
                    nPageFrame = j;
                    break;
                }
                else if (memory[j].nLoadedTime < nLoadedTime)
                { // 找到最早装入的页框
                    nPageFrame = j;
                    nLoadedTime = memory[j].nLoadedTime;
                }
            }

            // 页面置换
            memory[nPageFrame].nPageNum = VisitPage;
            memory[nPageFrame].nLoadedTime = i;
        }
    }

    return (float) PageHit / 320; // 命中率
}

float LRU(int MemoSize)
{
    int PageHit = 0;   // 命中次数

    for (int i = 0; i < 320; i++)
    {
        int VisitPage = test_sequence[i];
        int loc = InMemo(VisitPage, MemoSize);
        if (loc != -1)
        { // 命中
            PageHit++;
            memory[loc].nLastUsed = i;
        }
        else
        { // 缺页
            // 找到页框
            int nPageFrame = -1;
            int nLastUsed = inf;
            for (int j = 0; j < MemoSize; j++)
            {
                if (memory[j].nPageNum == -1)
                { // 找到空页框
                    nPageFrame = j;
                    break;
                }
                else if (memory[j].nLastUsed < nLastUsed)
                { // 找到最近最少使用页
                    nPageFrame = j;
                    nLastUsed = memory[j].nLastUsed;
                }
            }

            // 页面置换
            memory[nPageFrame].nPageNum = VisitPage;
            memory[nPageFrame].nLastUsed = i;
        }
    }

    return (float) PageHit / 320; // 命中率
}

int Find(int MemoSize, int step)
{ // OPT算法辅助函数
    
    // 检查是否存在空页
    for (int i = 0; i < MemoSize; i++)
    {
        if (memory[i].nPageNum == -1)
        { // 存在空页框
            return i;
        }
    }

    // 初始化
    for (int i = 0; i < MemoSize; i++)
    {
        memory[i].nNextUse = inf; 
    }

    // 统计下次使用时间
    for (int i = step + 1; i < 320; i++)
    {
        for (int j = 0; j < MemoSize; j++)
        {
            if (memory[j].nPageNum == test_sequence[i])
            { 
                memory[j].nNextUse = min(memory[j].nNextUse, i);
            }
        }
    }

    // 找到下次使用时间最晚的页框
    int nPageFrame = -1;
    int nNextUse = -1;
    for (int j = 0; j < MemoSize; j++)
    {
        if (memory[j].nNextUse > nNextUse)
        { // 找到下次使用时间最晚的页框
            nPageFrame = j;
            nNextUse = memory[j].nNextUse;
        }
    }

    return nPageFrame; // 返回页框
}

float OPT(int MemoSize)
{
    int PageHit = 0;   // 命中次数

    for (int i = 0; i < 320; i++)
    {
        int VisitPage = test_sequence[i];
        if (InMemo(VisitPage, MemoSize) != -1)
        { // 命中
            PageHit++;
        }
        else
        { // 缺页
            // 找到页框
            int nPageFrame = Find(MemoSize, i);

            // 页面置换
            memory[nPageFrame].nPageNum = VisitPage;
        }
    }

    return (float) PageHit / 320; // 命中率
}

int main()
{
    // 随机生成测试序列
    srand(0); // 设置随机数种子, 以便结果可复现
    for (int i = 0; i < 320; i++)
    {
        test_sequence[i] = rand() % 32 + 1; // 随机生成1-32的页号, 等价于随机生成0-320的指令再除以10
    }

    // 对每个算法，测试不同内存大小下的缺页率
    char *algorithms[] = {"FIFO", "LRU", "OPT"};
    for (int algo = 0; algo < 3; algo++)
    {
        printf("-----算法：%s-----\n", algorithms[algo]);
        for (int MemoSize = 4; MemoSize <= 32; MemoSize++)
        {
            init();
            float fRate;
            if (algo == 0)
            {
                fRate = FIFO(MemoSize); // FIFO
            }
            else if (algo == 1)
            {
                fRate = LRU(MemoSize); // LRU
            }
            else
            {
                fRate = OPT(MemoSize); // OPT
            }
            printf("%d page frames, rate %.2f%%\n", MemoSize, fRate * 100);
        }
        puts("");
    }
    
    return 0;
}