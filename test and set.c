#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

volatile int lock = 0;

int test_and_set(volatile int *lock) {
    int old_value = 1;
    asm volatile("xchg %0, %1" : "+r"(old_value), "+m"(*lock) :: "memory");
    return old_value;
}

void critical_section(int pid) {
    for (int i = 0; i < 3; i++) {
        while (test_and_set(&lock)); // Wait until the lock is free
        printf("Process %d is in the Critical Section\n", pid);
        sleep(1);
        lock = 0; // Release the lock
    }
}

int main() {
    for (int i = 0; i < 2; i++) { // Create two child processes
        pid_t pid = fork();
        if (pid == 0) { // Child process
            critical_section(i + 1);
            return 0;
        }
    }
    // Wait for child processes to complete
    while (wait(NULL) > 0);
    return 0;
}
