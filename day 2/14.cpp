#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 100
#define MAX_FILE_NAME 30

typedef struct {
    char name[MAX_FILE_NAME];
    int size;
} File;

File files[MAX_FILES];
int fileCount = 0;

void createFile(char *name, int size) {
    if (fileCount < MAX_FILES) {
        strcpy(files[fileCount].name, name);
        files[fileCount].size = size;
        fileCount++;
        printf("File '%s' created successfully.\n", name);
    } else {
        printf("Cannot create file. Maximum number of files reached.\n");
    }
}

void displayFiles() {
    printf("\nFiles in the directory:\n");
    for (int i = 0; i < fileCount; ++i) {
        printf("File Name: %s, Size: %d bytes\n", files[i].name, files[i].size);
    }
}

int main() {
    int choice, size;
    char fileName[MAX_FILE_NAME];

    do {
        printf("\nSingle-Level Directory Menu:\n");
        printf("1. Create File\n");
        printf("2. Display Files\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter file name: ");
                scanf("%s", fileName);
                printf("Enter file size (in bytes): ");
                scanf("%d", &size);
                createFile(fileName, size);
                break;
            case 2:
                displayFiles();
                break;
            case 0:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 0);

    return 0;
}

