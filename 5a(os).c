#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PORTS 3
#define NUM_THREADS 10

sem_t sem;

void* access_port(void* thread_id) {
    long id = (long)thread_id;  // Cast back to long for thread id
    printf("Thread %ld: Waiting to access a port...\n", id);
    sem_wait(&sem);
    printf("Thread %ld: Accessed a port!\n", id);
    sleep(5);
    printf("Thread %ld: Released a port!\n", id);
    sem_post(&sem);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    sem_init(&sem, 0, NUM_PORTS);  // Semaphore initialized with NUM_PORTS

    for (long i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, access_port, (void*)i);  // Casting i to void*
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);  // Wait for all threads to finish
    }

    sem_destroy(&sem);  // Destroy semaphore
    return 0;
}

