#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_PORTS 5
#define NUM_PROCESSES 10

typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int open_ports;
} PortMonitor;

PortMonitor monitor = { PTHREAD_MUTEX_INITIALIZER,
                        PTHREAD_COND_INITIALIZER,
                        MAX_PORTS };

// Function to request a port (Monitor function)
void request_port(int process_id) {
    pthread_mutex_lock(&monitor.mutex);

    while (monitor.open_ports <= 0) {
        printf("Process %d: Waiting for a free port...\n", process_id);
        pthread_cond_wait(&monitor.cond, &monitor.mutex);
    }

    monitor.open_ports--;
    printf("Process %d: Port opened (Remains: %d)\n",
           process_id, monitor.open_ports);

    pthread_mutex_unlock(&monitor.mutex);

    // Simulate using the port
    sleep(2);

    pthread_mutex_lock(&monitor.mutex);

    monitor.open_ports++;
    printf("Process %d: Port released (Now available: %d)\n",
           process_id, monitor.open_ports);

    pthread_cond_signal(&monitor.cond);
    pthread_mutex_unlock(&monitor.mutex);
}

// Thread function
void* process_thread(void* arg) {
    int process_id = *(int *)arg;
    request_port(process_id);
    return NULL;
}

// Main function
int main() {
    pthread_t threads[NUM_PROCESSES];
    int process_ids[NUM_PROCESSES];

    printf("Starting port monitor with %d max ports\n", MAX_PORTS);

    for (int i = 0; i < NUM_PROCESSES; i++) {
        process_ids[i] = i + 1; // Process IDs from 1 to NUM_PROCESSES
        pthread_create(&threads[i], NULL, process_thread, &process_ids[i]);
    }

    for (int i = 0; i < NUM_PROCESSES; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All processes completed\n");
    return 0;
}
