#include <stdio.h>
#include <stdlib.h>

int main() {
    // File creation and writing
    FILE *file = fopen("example_file.txt", "w");

    if (file == NULL) {
        perror("Error creating file");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "Hello, File Management in C!\n");
    fclose(file);

    // File reading
    file = fopen("example_file.txt", "r");

    if (file == NULL) {
        perror("Error opening file for reading");
        exit(EXIT_FAILURE);
    }

    char buffer[100];
    fscanf(file, "%99[^\n]", buffer);
    printf("Read from file: %s\n", buffer);

    fclose(file);

    // File appending
    file = fopen("example_file.txt", "a");

    if (file == NULL) {
        perror("Error opening file for appending");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "Appending more data.\n");
    fclose(file);

    // File reading after appending
    file = fopen("example_file.txt", "r");

    if (file == NULL) {
        perror("Error opening file for reading");
        exit(EXIT_FAILURE);
    }

    printf("\nContents after appending:\n");

    while (fscanf(file, "%99[^\n]", buffer) != EOF) {
        printf("%s\n", buffer);
    }

    fclose(file);

    return 0;
}

