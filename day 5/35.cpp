#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 100  // Adjust the maximum number of blocks as needed

struct IndexBlock {
    int blockPointers[MAX_BLOCKS];
};

struct Record {
    int id;
    // Add other fields as needed
};

void readRecord(FILE *file, struct IndexBlock *indexBlock, int recordNumber, struct Record *record) {
    int blockNumber = indexBlock->blockPointers[recordNumber - 1];

    fseek(file, blockNumber * sizeof(struct Record), SEEK_SET);
    fread(record, sizeof(struct Record), 1, file);
}

void writeRecord(FILE *file, struct IndexBlock *indexBlock, int recordNumber, struct Record *record) {
    int blockNumber = indexBlock->blockPointers[recordNumber - 1];

    fseek(file, blockNumber * sizeof(struct Record), SEEK_SET);
    fwrite(record, sizeof(struct Record), 1, file);
}

int main() {
    FILE *file;
    struct IndexBlock indexBlock;
    struct Record record;

    // Open the file in binary mode for both reading and writing
    file = fopen("indexed_file.dat", "r+b");

    if (file == NULL) {
        // If the file does not exist, create a new one
        file = fopen("indexed_file.dat", "w+b");
        if (file == NULL) {
            printf("Error creating the file.\n");
            return 1;
        }
    }

    // Initialize the index block
    for (int i = 0; i < MAX_BLOCKS; i++) {
        indexBlock.blockPointers[i] = i;  // Each entry points to its own block initially
    }

    // Menu for operations
    int choice;
    int recordNumber;

    do {
        printf("\n1. Read a record\n");
        printf("2. Write a record\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the record number to read: ");
                scanf("%d", &recordNumber);
                readRecord(file, &indexBlock, recordNumber, &record);
                printf("Record %d: ID %d\n", recordNumber, record.id);
                // Display other fields as needed
                break;

            case 2:
                printf("Enter the record number to write: ");
                scanf("%d", &recordNumber);
                printf("Enter the ID for the new record: ");
                scanf("%d", &record.id);
                // Get other fields as needed
                writeRecord(file, &indexBlock, recordNumber, &record);
                printf("Record %d written successfully.\n", recordNumber);
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

