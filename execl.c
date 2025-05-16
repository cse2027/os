#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
int main(){
printf("Before execl system call");
execl("/bin/ls","ls",(char *)0);
printf("After execl system call");
}
