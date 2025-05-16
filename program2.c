//write a c program to implement wait(),exit() system calls
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>

int main()
{
    int pid, i;
    pid = fork();

    if(pid < 0)
    {
        printf("FORK FAILED\n");
        exit(0);
    }
    else
    {
        if(pid == 0)
        {
            printf("CHILD PROCESS STARTS\n");
            for(i = 0; i < 5; i++)
            {
                printf("CHILD PROCESS %d called with id %d\n", i, getpid());
            }
            printf("CHILD PROCESS ENDS\n");
        }
        else
        {
            wait(0);
            printf("PARENT PROCESS ID = %d\n", getpid());
            printf("PARENT PROCESS ENDS\n");
        }
    }

    exit(0);
}

