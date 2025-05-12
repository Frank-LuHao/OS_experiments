#include <stdio.h>
#include "./src/manager.h"

int main()
{
    MemoryManager manager;
    init_memory(&manager, 640); // 初始化内存管理器，设置总内存大小为640KB

    int algorithm = 0; // 0表示首次适应算法，1表示最佳适应算法，2表示最坏适应算法
    printf("Choose the algorithm:\n");
    scanf("%d", &algorithm);

    int id = 1;
    while (1)
    {
        char command[5];
        printf("Enter the allocate or reclaim(a/r),or press other key to exit.\n");
        scanf("%s", command);

        if (command[0] != 'a' && command[0] != 'r')
        {
            break; // 退出循环
        }
        if (command[0] == 'a')
        {
            int size;
            printf("Enter the size and id of the memory block to allocate:\n");
            scanf("%d", &size);

            int addr = allocate_memory(&manager, size, id++, algorithm);
            
            if (addr == -1)
            {
                printf("Allocation failed.\n");
            }
            else
            {
                printf("Allocation successful. ADDRESS = %d\n", addr);
            }
        }
        else if (command[0] == 'r')
        {
            int DelId;
            printf("Enter the id of the memory block to reclaim:\n");
            scanf("%d", &DelId);

            int result = free_memory(&manager, DelId);
            if (result == -1)
            {
                printf("Reclaim failed.\n");
            }
            else
            {
                printf("Reclaim successful.\n");
            }
        }

        // 显示内存状态
        display_memory(&manager); // 显示内存状态
    }
    

    return 0;
}