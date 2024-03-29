#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

int main(int argc, char *argv[]) {
    // Check if the correct number of arguments is provided
    if (argc != 3) {
        printf("Usage: %s [pattern] [filename]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *pattern = argv[1];
    char *filename = argv[2];
    char line[MAX_LINE_LENGTH];

    // Open the file for reading
    FILE *file = fopen(filename, "r");

    // Check if file opening was successful
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Read and search for the pattern in each line
    printf("Lines containing '%s' in '%s':\n", pattern, filename);
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        if (strstr(line, pattern) != NULL) {
            printf("%s", line);
        }
    }

    // Close the file
    fclose(file);

    return 0;
}

