#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIRECTORIES 10
#define MAX_FILES_PER_DIRECTORY 10
#define MAX_DIRECTORY_NAME 30
#define MAX_FILE_NAME 30

typedef struct {
    char name[MAX_FILE_NAME];
    int size;
} File;

typedef struct {
    char name[MAX_DIRECTORY_NAME];
    File files[MAX_FILES_PER_DIRECTORY];
    int fileCount;
} Directory;

Directory directories[MAX_DIRECTORIES];
int directoryCount = 0;

void createDirectory(char *name) {
    if (directoryCount < MAX_DIRECTORIES) {
        strcpy(directories[directoryCount].name, name);
        directories[directoryCount].fileCount = 0;
        directoryCount++;
        printf("Directory '%s' created successfully.\n", name);
    } else {
        printf("Cannot create directory. Maximum number of directories reached.\n");
    }
}

void createFile(char *directoryName, char *fileName, int size) {
    int directoryIndex = -1;

    // Find the directory index
    for (int i = 0; i < directoryCount; ++i) {
        if (strcmp(directories[i].name, directoryName) == 0) {
            directoryIndex = i;
            break;
        }
    }

    if (directoryIndex != -1) {
        if (directories[directoryIndex].fileCount < MAX_FILES_PER_DIRECTORY) {
            File *file = &directories[directoryIndex].files[directories[directoryIndex].fileCount];
            strcpy(file->name, fileName);
            file->size = size;
            directories[directoryIndex].fileCount++;
            printf("File '%s' created in directory '%s' successfully.\n", fileName, directoryName);
        } else {
            printf("Cannot create file. Maximum number of files reached in directory '%s'.\n", directoryName);
        }
    } else {
        printf("Directory '%s' not found.\n", directoryName);
    }
}

void displayFiles() {
    printf("\nFiles in the directories:\n");

    for (int i = 0; i < directoryCount; ++i) {
        printf("Directory: %s\n", directories[i].name);

        for (int j = 0; j < directories[i].fileCount; ++j) {
            printf("  File Name: %s, Size: %d bytes\n", directories[i].files[j].name, directories[i].files[j].size);
        }
    }
}

int main() {
    int choice, size;
    char directoryName[MAX_DIRECTORY_NAME];
    char fileName[MAX_FILE_NAME];

    do {
        printf("\nTwo-Level Directory Menu:\n");
        printf("1. Create Directory\n");
        printf("2. Create File\n");
        printf("3. Display Files\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter directory name: ");
                scanf("%s", directoryName);
                createDirectory(directoryName);
                break;
            case 2:
                printf("Enter directory name: ");
                scanf("%s", directoryName);
                printf("Enter file name: ");
                scanf("%s", fileName);
                printf("Enter file size (in bytes): ");
                scanf("%d", &size);
                createFile(directoryName, fileName, size);
                break;
            case 3:
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

