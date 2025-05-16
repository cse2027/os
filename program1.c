//write a c program to implement fork() system call
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main()
{
    int pid, childpid;
    pid = getpid();  
    childpid = fork(); 

    if (childpid > 0) { 
        
        printf("I am parent process %d\n", pid);  
        printf("Child process ID is %d\n", childpid);  
    }
    else if (childpid == 0) {
        
        printf("I am child process %d\n", childpid);  
        printf("My process ID is %d\n", getpid());  
    }
    else {
        
        printf("FORK FAILED\n");
    }

    return 0;
}

