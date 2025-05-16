//shortest job first
#include <stdio.h>

void SJF(int at[], int bt[], int n) {
    float ttat = 0, tot = 0;
    int ct = 0, cmpt[10];

    // Sorting based on Burst Time (SJF Scheduling)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (bt[i] > bt[j]) {
                int temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;
                
                temp = at[i];
                at[i] = at[j];
                at[j] = temp;
            }
        }
    }

    printf("Arrival Time\tBurst Time\tTurnaround Time\tWaiting Time\tCompletion Time\n");

    for (int i = 0; i < n; i++) {
        if (ct < at[i]) {
            ct = at[i];
        }

        int tat = ct + bt[i] - at[i];
        int wt = tat - bt[i];
        ttat += tat;
        tot += wt;
        cmpt[i] = ct + bt[i];

        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", at[i], bt[i], tat, wt, cmpt[i]);
        ct += bt[i];
    }

    printf("\nAverage Turnaround Time: %.2f\n", ttat / n);
    printf("Average Waiting Time: %.2f\n", tot / n);
}

int main() {
    int n;
    int at[10], bt[10];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter process %d details:\n", i + 1);
        printf("Arrival time: ");
        scanf("%d", &at[i]);
        printf("Burst time: ");
        scanf("%d", &bt[i]);
    }

    SJF(at, bt, n);
    return 0;
}
