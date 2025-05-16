#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

#define NUM_ITERATIONS 5

int turn;
bool flag[2] = {false, false};

void *process0(void *args) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        flag[0] = true;
        turn = 1;
        while (flag[1] && turn == 1); // wait until process 1 exits
        
        // Critical Section
        printf("Process 0 is in the critical section.\n");
        sleep(1); // Simulate some work
        
        // Exit Section
        flag[0] = false;
    }
    return NULL;
}

void *process1(void *args) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        flag[1] = true;
        turn = 0;
        while (flag[0] && turn == 0); // wait until process 0 exits
        
        // Critical Section
        printf("Process 1 is in the critical section.\n");
        sleep(1); // Simulate some work
        
        // Exit Section
        flag[1] = false;
    }
    return NULL;
}

int main() {
    pthread_t t0, t1;
    pthread_create(&t0, NULL, process0, NULL);
    pthread_create(&t1, NULL, process1, NULL);

    pthread_join(t0, NULL);
    pthread_join(t1, NULL);

    printf("Both processes have finished execution.\n");
    return 0;
}
