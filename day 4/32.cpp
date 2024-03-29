#include <stdio.h>
#include <stdlib.h>

#define PAGE_FRAMES 3
#define MAX_PAGES 10

// Function to find the index of the least recently used page
int findLRUPage(int *counter, int pageFrames) {
    int minIndex = 0;
    for (int i = 1; i < pageFrames; ++i) {
        if (counter[i] < counter[minIndex]) {
            minIndex = i;
        }
    }
    return minIndex;
}

// Function to display the contents of the page table
void displayPageTable(int *pageTable, int pageFrames) {
    printf("Page Table: ");
    for (int i = 0; i < pageFrames; ++i) {
        printf("[%d] ", pageTable[i]);
    }
    printf("\n");
}

int main() {
    int pageReferences[MAX_PAGES] = {0, 1, 2, 3, 0, 1, 4, 0, 1, 2};
    int pageTable[PAGE_FRAMES];
    int counter[PAGE_FRAMES] = {0};
    int pageFaults = 0;

    // Initialize page table
    for (int i = 0; i < PAGE_FRAMES; ++i) {
        pageTable[i] = -1;
    }

    // Simulate LRU page replacement algorithm
    for (int i = 0; i < MAX_PAGES; ++i) {
        printf("Page Reference: %d\n", pageReferences[i]);

        int page = pageReferences[i];
        int pageFound = 0;

        // Check if the page is already in the page table
        for (int j = 0; j < PAGE_FRAMES; ++j) {
            if (pageTable[j] == page) {
                pageFound = 1;
                counter[j] = i;  // Update the counter for the referenced page
                printf("Page Hit!\n");
                break;
            }
        }

        if (!pageFound) {
            // Page fault occurred, find the least recently used page
            int lruIndex = findLRUPage(counter, PAGE_FRAMES);
            pageTable[lruIndex] = page;
            counter[lruIndex] = i;
            pageFaults++;
            printf("Page Fault!\n");
        }

        // Display the contents of the page table after each page reference
        displayPageTable(pageTable, PAGE_FRAMES);
        printf("\n");
    }

    printf("Total Page Faults: %d\n", pageFaults);

    return 0;
}

