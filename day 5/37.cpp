#include <stdio.h>
#include <stdlib.h>

// Function to calculate the total head movement
int calculateTotalHeadMovement(int requestQueue[], int n, int initialHead) {
    int totalHeadMovement = 0;
    int currentHead = initialHead;

    for (int i = 0; i < n; i++) {
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

    // Calculate total head movement using FCFS algorithm
    int totalHeadMovement = calculateTotalHeadMovement(requestQueue, n, initialHead);

    // Display the results
    printf("\nTotal Head Movement: %d\n", totalHeadMovement);

    return 0;
}

