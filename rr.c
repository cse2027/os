// Aim: To write a
// C program to implement
// Round Robin CPU scheduler.

#include <stdio.h>

void get_input(int *n, int at[], int bt[], int *quantum) {
    printf("Enter number of processes: ");
    scanf("%d", n);

    for (int i = 0; i < *n; i++) {
        printf("Enter arrival and burst time for process %d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
    }

    printf("Enter time quantum: ");
    scanf("%d", quantum);
}

void rr_gantt(int n, int at[], int bt[], int quantum) {
    int wt[n], tat[n], rem_bt[n];
    for (int i = 0; i < n; i++) {
        rem_bt[i] = bt[i];
        wt[i] = 0;
        tat[i] = 0;
    }

    int time = 0, completed = 0;

    while (completed < n) {
        int all_done = 1;
        for (int i = 0; i < n; i++) {
            if (rem_bt[i] > 0) {
                all_done = 0;
                int executed = (rem_bt[i] < quantum) ? rem_bt[i] : quantum;
                rem_bt[i] -= executed;
                time += executed;
                if (rem_bt[i] == 0) {
                    tat[i] = time - at[i];
                    wt[i] = tat[i] - bt[i];
                    completed++;
                }
            }
        }
        if (all_done) break;
    }

    printf("Process\tArrival\tBurst\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], tat[i], wt[i]);
    }
}

int main() {
    int n, quantum;
    int at[10], bt[10];
    get_input(&n, at, bt, &quantum);
    rr_gantt(n, at, bt, quantum);
    return 0;
}
