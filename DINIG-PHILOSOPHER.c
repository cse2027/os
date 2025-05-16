#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NOM_PHILOSOPHERS 5
#define MAX_MEALS 2

sem_t mutex;
sem_t forks[NOM_PHILOSOPHERS];

void *philosopher(void *num) {
    int phil = *(int *)num;
    int left = phil;
    int right = (phil + 1) % NOM_PHILOSOPHERS;
    int meals_eaten = 0;

    while (meals_eaten < MAX_MEALS) {
        printf("Philosopher %d is thinking\n", phil);
        sleep(rand() % 3 + 1);

        sem_wait(&forks[left]);
        printf("Philosopher %d picked up left fork %d\n", phil, left);

        sem_wait(&forks[right]);
        printf("Philosopher %d picked up right fork %d\n", phil, right);

        printf("Philosopher %d is eating\n", phil);
        sleep(rand() % 3 + 1);
        meals_eaten++;

        sem_post(&forks[right]);
        printf("Philosopher %d put down right fork %d\n", phil, right);

        sem_post(&forks[left]);
        printf("Philosopher %d put down left fork %d\n", phil, left);
    }
    printf("Philosopher %d finished eating\n", phil);
    pthread_exit(NULL);
}

int main() {
    pthread_t philosophers[NOM_PHILOSOPHERS];
    int philosopher_ids[NOM_PHILOSOPHERS];

    sem_init(&mutex, 0, 1);
    for (int i = 0; i < NOM_PHILOSOPHERS; i++) {
        sem_init(&forks[i], 0, 1);
    }

    for (int i = 0; i < NOM_PHILOSOPHERS; i++) {
        philosopher_ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
    }

    for (int i = 0; i < NOM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    for (int i = 0; i < NOM_PHILOSOPHERS; i++) {
        sem_destroy(&forks[i]);
    }
    
    sem_destroy(&mutex);
    return 0;
}
