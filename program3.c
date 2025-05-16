//write a c program to implement wait() and exit() system calls
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main()
{
    pid_t pid;
    int rv;
    pid = fork();

    switch(pid)
    {
        case -1: 
            perror("FORK");
            exit(1);
        
        case 0: 
            printf("in child: my pid is %d\n", getpid());
            printf("in child: my parent is %d\n", getppid());
            printf("in child: my exit status\n");
            printf("child: I am out here\n");
            scanf("%d", &rv);
            exit(rv);

        default:
            printf("in parent: I am parent process\n");
            printf("parent: MYPID : %d\n", getpid());
            fflush(stdout);
            wait(&rv);
            fflush(stdout);
            printf("parent: my child is %d\n", pid);
            printf("parent: I am waiting for my child to exit\n");
            fflush(stdout);
            printf("parent: my child exit status is %d\n", WEXITSTATUS(rv));
            printf("parent: I am out\n");
    }

    return 0;
}

