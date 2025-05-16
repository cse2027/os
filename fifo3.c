#include <stdio.h>

int main() {
    int pages[100], n, capacity;
    int memory[100], front = 0, rear = 0;
    int pageFaults = 0, i, j, found;

    printf("Enter the number of pages: ");
    scanf("%d", &n);

    printf("Enter the page sequence:\n");
    for(i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter the frame capacity: ");
    scanf("%d", &capacity);

    int count = 0; // current number of pages in memory

    printf("\nPage\tMemory\n");
    for(i = 0; i < n; i++) {
        found = 0;

        // Check if page is already in memory
        for(j = 0; j < count; j++) {
            if(memory[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if(!found) {
            // Page fault occurs
            pageFaults++;

            if(count < capacity) {
                memory[rear] = pages[i];
                rear = (rear + 1) % capacity;
                count++;
            } else {
                memory[front] = pages[i];
                front = (front + 1) % capacity;
                rear = (rear + 1) % capacity;
            }
        }

        // Print memory status
        printf("%d\t", pages[i]);
        for(j = 0; j < count; j++) {
            printf("%d ", memory[(front + j) % capacity]);
        }
        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", pageFaults);
    return 0;
}
