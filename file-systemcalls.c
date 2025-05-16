#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char data[100];

    file = fopen("example.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing\n");
        return 1;
    }

    printf("Enter data to write into the file: ");
    fgets(data, sizeof(data), stdin);
    fprintf(file, "%s", data);
    printf("Data written to the file successfully\n");
    fclose(file);

    file = fopen("example.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading\n");
        return 1;
    }

    printf("Reading data from the file...\n");
    while (fgets(data, sizeof(data), file)) {
        printf("%s", data);
    }

    fclose(file);
    return 0;
}
