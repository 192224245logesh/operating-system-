#include <stdio.h>
#include <stdlib.h>

#define MAX_RECORDS 100  // Adjust the maximum number of records as needed

struct Record {
    int id;
    // Add other fields as needed
};

void readRecord(FILE *file, int recordNumber, struct Record *record) {
    fseek(file, (recordNumber - 1) * sizeof(struct Record), SEEK_SET);
    fread(record, sizeof(struct Record), 1, file);
}

void writeRecord(FILE *file, int recordNumber, struct Record *record) {
    fseek(file, (recordNumber - 1) * sizeof(struct Record), SEEK_SET);
    fwrite(record, sizeof(struct Record), 1, file);
}

int main() {
    FILE *file;
    struct Record record;

    // Open the file in binary mode for both reading and writing
    file = fopen("sequential_file.dat", "r+b");

    if (file == NULL) {
        // If the file does not exist, create a new one
        file = fopen("sequential_file.dat", "w+b");
        if (file == NULL) {
            printf("Error creating the file.\n");
            return 1;
        }
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
                readRecord(file, recordNumber, &record);
                printf("Record %d: ID %d\n", recordNumber, record.id);
                // Display other fields as needed
                break;

            case 2:
                printf("Enter the record number to write: ");
                scanf("%d", &recordNumber);
                printf("Enter the ID for the new record: ");
                scanf("%d", &record.id);
                // Get other fields as needed
                writeRecord(file, recordNumber, &record);
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

