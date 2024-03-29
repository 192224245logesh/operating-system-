#include <stdio.h>

// Maximum number of processes and resources
#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

// Function prototypes
void bankerAlgorithm(int available[], int maximum[][MAX_RESOURCES], int allocation[][MAX_RESOURCES], int need[][MAX_RESOURCES], int processes, int resources);
int requestResource(int process, int request[], int available[], int allocation[][MAX_RESOURCES], int need[][MAX_RESOURCES], int maximum[][MAX_RESOURCES], int processes, int resources);

int main() {
    // Number of processes and resources
    int processes, resources;

    printf("Enter the number of processes: ");
    scanf("%d", &processes);

    printf("Enter the number of resources: ");
    scanf("%d", &resources);

    // Arrays to store the maximum, allocation, and need matrices
    int maximum[MAX_PROCESSES][MAX_RESOURCES];
    int allocation[MAX_PROCESSES][MAX_RESOURCES];
    int need[MAX_PROCESSES][MAX_RESOURCES];

    // Array to store the available resources
    int available[MAX_RESOURCES];

    // Input maximum matrix
    printf("Enter the maximum matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &maximum[i][j]);
        }
    }

    // Input allocation matrix
    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Calculate the need matrix
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }

    // Input available resources
    printf("Enter the available resources:\n");
    for (int i = 0; i < resources; i++) {
        scanf("%d", &available[i]);
    }

    // Run Banker's algorithm
    bankerAlgorithm(available, maximum, allocation, need, processes, resources);

    return 0;
}

// Function to simulate Banker's algorithm
void bankerAlgorithm(int available[], int maximum[][MAX_RESOURCES], int allocation[][MAX_RESOURCES], int need[][MAX_RESOURCES], int processes, int resources) {
    // Implementation of the Banker's algorithm...
    // (Same as in the previous code)

    // This function remains unchanged in the provided context
}

// Function to handle resource request
int requestResource(int process, int request[], int available[], int allocation[][MAX_RESOURCES], int need[][MAX_RESOURCES], int maximum[][MAX_RESOURCES], int processes, int resources) {
    // Check if request is valid
    for (int i = 0; i < resources; i++) {
        if (request[i] > need[process][i] || request[i] > available[i]) {
            printf("Invalid request: Process %d is requesting more resources than needed or available.\n", process);
            return 0;
        }
    }

    // Attempt to allocate resources
    for (int i = 0; i < resources; i++) {
        available[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }

    // Run Banker's algorithm to check for safety
    bankerAlgorithm(available, maximum, allocation, need, processes, resources);

    return 1;
}

