#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

int main() {
    // Open a file
    FILE *file = fopen("example_file.txt", "w+");

    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Move to a specific position in the file
    fseek(file, 10, SEEK_SET);

    // Get file information
    struct stat fileStat;
    if (stat("example_file.txt", &fileStat) == -1) {
        perror("Error getting file information");
    } else {
        printf("File Size: %ld bytes\n", fileStat.st_size);
        printf("File Permissions: %o\n", fileStat.st_mode & (S_IRUSR | S_IWUSR));
    }

    // Read and display directory contents
    DIR *directory = opendir(".");
    struct dirent *entry;

    if (directory == NULL) {
        perror("Error opening directory");
    } else {
        printf("\nFiles in the current directory:\n");

        while ((entry = readdir(directory)) != NULL) {
            printf("%s\n", entry->d_name);
        }

        closedir(directory);
    }

    // Close the file
    fclose(file);

    return 0;
}

