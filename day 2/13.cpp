#include <stdio.h>

#define MEMORY_SIZE 100

typedef struct Block {
    int size;
    int allocated;
} Block;

Block memory[MEMORY_SIZE];

// Function prototypes
void initializeMemory();
void displayMemory();
void firstFit(int processSize);
void bestFit(int processSize);
void worstFit(int processSize);

int main() {
    int choice, processSize;

    initializeMemory();

    do {
        printf("\nMemory Allocation Strategies:\n");
        printf("1. First Fit\n");
        printf("2. Best Fit\n");
        printf("3. Worst Fit\n");
        printf("4. Display Memory\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter process size: ");
                scanf("%d", &processSize);
                firstFit(processSize);
                break;
            case 2:
                printf("Enter process size: ");
                scanf("%d", &processSize);
                bestFit(processSize);
                break;
            case 3:
                printf("Enter process size: ");
                scanf("%d", &processSize);
                worstFit(processSize);
                break;
            case 4:
                displayMemory();
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

void initializeMemory() {
    for (int i = 0; i < MEMORY_SIZE; ++i) {
        memory[i].size = 0;
        memory[i].allocated = 0;
    }
}

void displayMemory() {
    printf("\nMemory State:\n");
    for (int i = 0; i < MEMORY_SIZE; ++i) {
        if (memory[i].allocated) {
            printf("Allocated Block: %d\n", memory[i].size);
        } else {
            printf("Free Block: %d\n", memory[i].size);
        }
    }
}

void firstFit(int processSize) {
    for (int i = 0; i < MEMORY_SIZE; ++i) {
        if (!memory[i].allocated && memory[i].size >= processSize) {
            memory[i].allocated = 1;
            printf("Process of size %d allocated using First Fit.\n", processSize);
            return;
        }
    }
    printf("Memory allocation failed for process of size %d using First Fit.\n", processSize);
}

void bestFit(int processSize) {
    int bestFitIndex = -1;
    int bestFitSize = MEMORY_SIZE + 1;

    for (int i = 0; i < MEMORY_SIZE; ++i) {
        if (!memory[i].allocated && memory[i].size >= processSize) {
            if (memory[i].size < bestFitSize) {
                bestFitSize = memory[i].size;
                bestFitIndex = i;
            }
        }
    }

    if (bestFitIndex != -1) {
        memory[bestFitIndex].allocated = 1;
        printf("Process of size %d allocated using Best Fit.\n", processSize);
    } else {
        printf("Memory allocation failed for process of size %d using Best Fit.\n", processSize);
    }
}

void worstFit(int processSize) {
    int worstFitIndex = -1;
    int worstFitSize = -1;

    for (int i = 0; i < MEMORY_SIZE; ++i) {
        if (!memory[i].allocated && memory[i].size >= processSize) {
            if (memory[i].size > worstFitSize) {
                worstFitSize = memory[i].size;
                worstFitIndex = i;
            }
        }
    }

    if (worstFitIndex != -1) {
        memory[worstFitIndex].allocated = 1;
        printf("Process of size %d allocated using Worst Fit.\n", processSize);
    } else {
        printf("Memory allocation failed for process of size %d using Worst Fit.\n", processSize);
    }
}

