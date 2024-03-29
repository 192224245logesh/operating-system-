#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    DIR *directory;
    struct dirent *entry;

    // Open the specified directory or the current directory if no argument is provided
    if (argc == 1) {
        directory = opendir(".");
    } else if (argc == 2) {
        directory = opendir(argv[1]);
    } else {
        printf("Usage: %s [directory]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Check if directory opening was successful
    if (directory == NULL) {
        perror("Error opening directory");
        exit(EXIT_FAILURE);
    }

    // Read and display directory contents
    printf("Contents of the directory:\n");
    while ((entry = readdir(directory)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    // Close the directory
    closedir(directory);

    return 0;
}

