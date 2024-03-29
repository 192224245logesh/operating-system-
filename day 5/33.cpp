#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 3  // Adjust the number of frames as needed

int findOptimal(int pages[], int n, int frames[], int frameCount) {
    int index = -1, farthest = -1;
    for (int i = 0; i < frameCount; i++) {
        int j;
        for (j = n; j >= 0; j--) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    index = i;
                }
                break;
            }
        }
        if (j == -1)
            return i;  // If a page is not found in future, return its index
    }
    return (index == -1) ? 0 : index;
}

void optimalPageReplacement(int pages[], int n, int frameCount) {
    int frames[frameCount];
    int pageFaults = 0;

    for (int i = 0; i < frameCount; i++)
        frames[i] = -1;

    printf("Page Reference Sequence: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", pages[i]);

        int pageFound = 0;
        for (int j = 0; j < frameCount; j++) {
            if (frames[j] == pages[i]) {
                pageFound = 1;
                break;
            }
        }

        if (!pageFound) {
            int replaceIndex = findOptimal(pages, i + 1, frames, frameCount);
            frames[replaceIndex] = pages[i];
            pageFaults++;
        }
    }

    printf("\nNumber of Page Faults: %d\n", pageFaults);
}

int main() {
    int n;

    printf("Enter the number of pages: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter the page reference sequence:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    int frameCount;
    printf("Enter the number of frames: ");
    scanf("%d", &frameCount);

    optimalPageReplacement(pages, n, frameCount);

    return 0;
}

