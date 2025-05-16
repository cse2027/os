//Shortest remaining time
#include <stdio.h>
#include <limits.h>

void srtf(int at[], int bt[], int n)
{
    int ttat = 0, twt = 0, ct = 0, rt[n], cmpc[n];
    int completed = 0;

    for (int i = 0; i < n; i++)
    {
        rt[i] = bt[i];
        cmpc[i] = 0;
    }

    printf("Arrival Time\tBurst Time\tTurnaround Time\tWaiting Time\n");

    while (completed != n)
    {
        int min_rt = INT_MAX, min_index = -1;
        
        for (int i = 0; i < n; i++)
        {
            if (at[i] <= ct && rt[i] < min_rt && rt[i] > 0)
            {
                min_rt = rt[i];
                min_index = i;
            }
        }

        if (min_index == -1)
        {
            ct++;
            continue;
        }

        rt[min_index]--;
        ct++;
        
        if (rt[min_index] == 0)
        {
            int tat = ct - at[min_index];
            int wt = tat - bt[min_index];
            
            ttat += tat;
            twt += wt;
            cmpc[min_index] = 1;
            completed++;
            
            printf("%d\t%d\t%d\t%d\n", at[min_index], bt[min_index], tat, wt);
        }
    }

    printf("Average Turnaround Time: %.2f\n", (float)ttat / n);
    printf("Average Waiting Time: %.2f\n", (float)twt / n);
}

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    int at[n], bt[n];
    
    for (int i = 0; i < n; i++)
    {
        printf("Enter process %d details:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
    }
    
    srtf(at, bt, n);
    
    return 0;
}
