#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    pid_t childpid;
    int retval; //子进程返回值
    int status;
    childpid=fork();
    if(childpid >= 0)
    {
        if(childpid == 0)
        {
            printf("CHILD: I am the child process! \n");
            printf("CHILD: Here's my PID: %d\n", getpid());//获取当前PID
            printf("CHILD: My parent's PID is: %d\n", getppid());//获取父进程PID
            printf("CHILD: The value of fork return is: %d\n", childpid);
            printf("CHILD: Sleep for 1 second...\n");
            sleep(1);
            printf("CHILD: Enter an exit value (0~255):");
            scanf("%d",&retval);
            printf("CHILD: Google! \n");
            exit(retval);
        }
        else
        {
            printf("Parent, I am the parent process! \n");
            printf("Parent: Here's my PID: %d\n", getpid());   //获取当前PID
            printf("Parent: The value of my child's PID is: %d\n", childpid);
            printf("Parent: I will now wait for my child to exit.\n");
            wait(&status); //等待并收回子进程
            printf("Parent: Child's exit code is: %d\n", WEXITSTATUS(status));
            printf("Parent: Google! \n");
            exit(0);
        }
    }
    else
    {
        perror("fork error!");
        exit(0);
    }

    return 0;
}