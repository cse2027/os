#include <stdio.h>
#include <unistd.h>
#include <stdatomic.h>
#include <sys/wait.h>  // Include this for wait()

volatile int lock = 0;

int compare_and_swap(volatile int* lock, int expected, int new_value) {
    int old = expected;
    __atomic_compare_exchange_n(lock, &old, new_value, 0, __ATOMIC_ACQUIRE, __ATOMIC_RELAXED);
    return old;
}

void critical_section(int pid) {
    for (int i = 0; i < 3; i++) {
        while (compare_and_swap(&lock, 0, 1) != 0);
        printf("Process %d is in the critical section\n", pid);
        sleep(1);
        lock = 0;
    }
}

int main() {
    for (int i = 1; i <= 2; i++) {
        pid_t pid = fork();
        if (pid == 0) { // Child process
            critical_section(i);
            return 0;
        }
    }
    // Wait for child processes to complete
    while (wait(NULL) > 0);
    return 0;
}
