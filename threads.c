// Write a C program to implement even and odd threads

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *print_even(void *args) {
    for (int i = 2; i <= 10; i += 2) {
        printf("Even: %d\n", i);
    }
    return NULL;
}

void *print_odd(void *args) {
    for (int i = 1; i <= 10; i += 2) {
        printf("Odd: %d\n", i);
    }
    return NULL;
}

int main() {
    pthread_t even_thread, odd_thread;

    // Creating threads
    pthread_create(&even_thread, NULL, print_even, NULL);
    pthread_create(&odd_thread, NULL, print_odd, NULL);

    // Waiting for threads to finish
    pthread_join(even_thread, NULL);
    pthread_join(odd_thread, NULL);

    // Exit main thread
    pthread_exit(NULL);

    return 0;
}
