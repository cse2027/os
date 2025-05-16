// Write a C program to implement priority scheduling algorithm

#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int bt[n], pt[n], pid[n];

    for (int i = 0; i < n; i++) {
        printf("Enter Burst Time and Priority Value for process %d: ", i + 1);
        scanf("%d %d", &bt[i], &pt[i]);
        pid[i] = i + 1;
    }

    // Sorting processes based on priority (lower value = higher priority)
    for (int i = 0; i < n - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < n; j++) {
            if (pt[j] < pt[min_index]) {
                min_index = j;
            }
        }
        swap(&bt[i], &bt[min_index]);
        swap(&pid[i], &pid[min_index]);
        swap(&pt[i], &pt[min_index]);
    }

    int t = 0;
    printf("\nOrder of process execution:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d is executed from %d to %d\n", pid[i], t, t + bt[i]);
        t += bt[i];
    }

    printf("\nProcess Id\tBurst Time\tWaiting Time\tTurnaround Time\n");
    int wt = 0;
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\n", pid[i], bt[i], wt, wt + bt[i]);
        wt += bt[i];
    }

    return 0;
}
