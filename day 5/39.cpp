#include <stdio.h>
#include <stdlib.h>

// Function to calculate the total head movement for C-SCAN algorithm
int calculateTotalHeadMovement_CSCAN(int requestQueue[], int n, int initialHead, int direction, int diskSize) {
    int totalHeadMovement = 0;
    int currentHead = initialHead;

    // Sort the request queue in ascending order
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (requestQueue[j] > requestQueue[j + 1]) {
                // Swap requests if they are out of order
                int temp = requestQueue[j];
                requestQueue[j] = requestQueue[j + 1];
                requestQueue[j + 1] = temp;
            }
        }
    }

    // Find the position of initial head in the sorted request queue
    int initialHeadPosition = 0;
    while (requestQueue[initialHeadPosition] < currentHead && initialHeadPosition < n) {
        initialHeadPosition++;
    }

    // Move towards higher-numbered tracks
    for (int i = initialHeadPosition; i < n; i++) {
        totalHeadMovement += abs(requestQueue[i] - currentHead);
        currentHead = requestQueue[i];
    }

    // If direction is right, add the head movement to the end of the disk
    if (direction == 1) {
        totalHeadMovement += abs(diskSize - currentHead);
        currentHead = 0;
    }

    // Move towards lower-numbered tracks
    for (int i = 0; i < initialHeadPosition; i++) {
        totalHeadMovement += abs(requestQueue[i] - currentHead);
        currentHead = requestQueue[i];
    }

    return totalHeadMovement;
}

int main() {
    int n;

    printf("Enter the number of requests: ");
    scanf("%d", &n);

    int requestQueue[n];

    printf("Enter the disk requests:\n");
    for (int i = 0; i < n; i++) {
        printf("Request %d: ", i + 1);
        scanf("%d", &requestQueue[i]);
    }

    int initialHead;

    printf("Enter the initial head position: ");
    scanf("%d", &initialHead);

    int direction;

    printf("Enter the direction (1 for towards higher-numbered tracks, 0 for towards lower-numbered tracks): ");
    scanf("%d", &direction);

    int diskSize;

    printf("Enter the disk size: ");
    scanf("%d", &diskSize);

    // Calculate total head movement using C-SCAN algorithm
    int totalHeadMovement = calculateTotalHeadMovement_CSCAN(requestQueue, n, initialHead, direction, diskSize);

    // Display the results
    printf("\nTotal Head Movement: %d\n", totalHeadMovement);

    return 0;
}

