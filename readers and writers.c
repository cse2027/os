#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READERS 5
#define NUM_WRITERS 3
#define MAX_OPS 5   

int shared_data = 0;
sem_t mutex;
sem_t write_lock;
int read_count = 0;
int read_ops = 0, write_ops = 0;

void *reader(void *arg) {
    int reader_id = *((int *)arg);
    while (1) {
        sem_wait(&mutex);
        read_count++;
        if (read_count == 1) {
            sem_wait(&write_lock);
        }
        sem_post(&mutex);

        printf("Reader %d: Read shared data = %d\n", reader_id, shared_data);

        sem_wait(&mutex);
        read_count--;
        if (read_count == 0) {
            sem_post(&write_lock);
        }
        sem_post(&mutex);
        
        read_ops++;
        if (read_ops >= MAX_OPS)
            break;
        usleep(rand() % 3000000);
    }
    return NULL;
}

void *writer(void *arg) {
    int writer_id = *((int *)arg);
    while (1) {
        sem_wait(&write_lock);
        shared_data = rand() % 100;
        printf("Writer %d: wrote shared data = %d\n", writer_id, shared_data);
        sem_post(&write_lock);
        
        write_ops++;
        if (write_ops >= MAX_OPS)
            break;
        usleep(rand() % 3000000);
    }
    return NULL;
}

int main() {
    pthread_t readers[NUM_READERS];
    pthread_t writers[NUM_WRITERS];
    int reader_ids[NUM_READERS];
    int writer_ids[NUM_WRITERS];

    sem_init(&mutex, 0, 1);
    sem_init(&write_lock, 0, 1);

    for (int i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, (void *)&reader_ids[i]);
    }

    for (int j = 0; j < NUM_WRITERS; j++) {
        writer_ids[j] = j + 1;
        pthread_create(&writers[j], NULL, writer, (void *)&writer_ids[j]);
    }

    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }

    for (int j = 0; j < NUM_WRITERS; j++) {
        pthread_join(writers[j], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&write_lock);

    return 0;
}
