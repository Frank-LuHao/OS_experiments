#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    pid_t childpid;

    childpid = fork(); // 创建子进程
    if (childpid < 0)
    {
        // fork失败
        perror("fork error");
        exit(1);
    }
    else if (childpid == 0)
    {
        // 子进程
        printf("CHILD: I am the child process. Executing 'ls' command...\n");
        execlp("ls", "ls", "-l", NULL); // 使用execlp执行ls命令
        // 如果execlp执行失败
        perror("execlp error");
        exit(1);
    }
    else
    {
        // 父进程
        int status;
        printf("PARENT: I am the parent process. Waiting for child to finish...\n");
        wait(&status); // 等待子进程结束
        if (WIFEXITED(status))
        {
            printf("PARENT: Child exited with status: %d\n", WEXITSTATUS(status));
        }
        else
        {
            printf("PARENT: Child did not exit normally.\n");
        }
    }

    return 0;
}