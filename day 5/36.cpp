#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // Include this header for strlen and memcpy

#define BLOCK_SIZE 512
#define MAX_BLOCKS 100

struct DiskBlock {
    char data[BLOCK_SIZE];
    int nextBlock;
};

struct File {
    int firstBlock;
    int lastBlock;
};

void readBlock(FILE *file, int blockNumber, struct DiskBlock *block) {
    fseek(file, blockNumber * sizeof(struct DiskBlock), SEEK_SET);
    fread(block, sizeof(struct DiskBlock), 1, file);
}

void writeBlock(FILE *file, int blockNumber, struct DiskBlock *block) {
    fseek(file, blockNumber * sizeof(struct DiskBlock), SEEK_SET);
    fwrite(block, sizeof(struct DiskBlock), 1, file);
}

void readFile(FILE *file, struct File *fileEntry) {
    int currentBlock = fileEntry->firstBlock;
    struct DiskBlock block;

    printf("File contents:\n");

    while (currentBlock != -1) {
        readBlock(file, currentBlock, &block);
        printf("%s", block.data);
        currentBlock = block.nextBlock;
    }

    printf("\n");
}

void writeFile(FILE *file, struct File *fileEntry, const char *content) {
    int contentLength = strlen(content);
    int remainingBytes = contentLength;
    int currentBlock = fileEntry->firstBlock;

    struct DiskBlock block;

    while (currentBlock != -1 && remainingBytes > 0) {
        readBlock(file, currentBlock, &block);

        int bytesToCopy = (remainingBytes < BLOCK_SIZE) ? remainingBytes : BLOCK_SIZE;
        memcpy(block.data, content + (contentLength - remainingBytes), bytesToCopy);
        remainingBytes -= bytesToCopy;

        writeBlock(file, currentBlock, &block);

        currentBlock = block.nextBlock;
    }

    if (remainingBytes > 0) {
        // Allocate new blocks for the remaining content
        while (remainingBytes > 0) {
            int newBlock = ftell(file) / sizeof(struct DiskBlock);
            struct DiskBlock newBlockData;

            int bytesToCopy = (remainingBytes < BLOCK_SIZE) ? remainingBytes : BLOCK_SIZE;
            memcpy(newBlockData.data, content + (contentLength - remainingBytes), bytesToCopy);
            remainingBytes -= bytesToCopy;

            if (currentBlock == -1) {
                fileEntry->firstBlock = newBlock;
                fileEntry->lastBlock = newBlock;
            } else {
                block.nextBlock = newBlock;
                writeBlock(file, currentBlock, &block);
                fileEntry->lastBlock = newBlock;
            }

            newBlockData.nextBlock = -1;
            writeBlock(file, newBlock, &newBlockData);
            currentBlock = newBlock;
        }
    }
}

int main() {
    FILE *file;
    struct File fileEntry;

    // Open the file in binary mode for both reading and writing
    file = fopen("linked_file.dat", "r+b");

    if (file == NULL) {
        // If the file does not exist, create a new one
        file = fopen("linked_file.dat", "w+b");
        if (file == NULL) {
            printf("Error creating the file.\n");
            return 1;
        }
    }

    // Initialize the file entry
    fileEntry.firstBlock = -1;
    fileEntry.lastBlock = -1;

    // Menu for operations
    int choice;
    char content[500];

    do {
        printf("\n1. Read the file\n");
        printf("2. Write to the file\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                readFile(file, &fileEntry);
                break;

            case 2:
                printf("Enter the content to write: ");
                scanf(" %[^\n]", content);
                writeFile(file, &fileEntry, content);
                printf("Content written to the file.\n");
                break;

            case 3:
                printf("Exiting the program.\n");
                break;

            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (choice != 3);

    fclose(file);

    return 0;
}

