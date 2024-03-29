#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;

    // Open a file for writing
    file = fopen("example_file.txt", "w");

    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Write data to the file
    fprintf(file, "Hello, File Management in C!");

    // Close the file
    fclose(file);

    // Open the file for reading
    file = fopen("example_file.txt", "r");

    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Read data from the file
    char buffer[100];
    fscanf(file, "%99[^\n]", buffer);

    // Display the read data
    printf("Read from file: %s\n", buffer);

    // Close the file
    fclose(file);

    return 0;
}

