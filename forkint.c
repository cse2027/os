#include <stdio.h>
#include <unistd.h>
#include<stdlib.h>
int main()
{
    int id, i;
    id = fork();

    printf("Here the main function starts\n");

    if (id > 0) {
        printf("this is parent section\n");
    }
    else if (id == 0) {
        printf("\nthis is child section\n");
    }
    else {
        printf("\nhere creation of fork failed!!!\n");
    }

    printf("here we are printing the number from 1 to 10 with pid : %d\n",getpid());
    for (i = 1; i <= 10; i++)
        printf("%d ", i);
    printf("\n");
    exit(0);
}

