#include <stdio.h>
#include <stdlib.h>

#define PAGE_FRAMES 3
#define MAX_PAGES 10

// Function to check if a page is present in the page table
int isPagePresent(int page, int *pageTable, int pageFrames) {
    for (int i = 0; i < pageFrames; ++i) {
        if (pageTable[i] == page) {
            return 1; // Page is present
        }
    }
    return 0; // Page is not present
}

// Function to display the contents of the page table
void displayPageTable(int *pageTable, int pageFrames) {
    printf("Page Table: ");
    for (int i = 0; i < pageFrames; ++i) {
        if (pageTable[i] == -1) {
            printf("[ ] ");
        } else {
            printf("[%d] ", pageTable[i]);
        }
    }
    printf("\n");
}

int main() {
    int pageReferences[MAX_PAGES] = {0, 1, 2, 3, 0, 1, 4, 0, 1, 2};
    int pageTable[PAGE_FRAMES];
    int pageFaults = 0;

    // Initialize page table with -1 indicating empty frames
    for (int i = 0; i < PAGE_FRAMES; ++i) {
        pageTable[i] = -1;
    }

    // Simulate FIFO page replacement algorithm
    for (int i = 0; i < MAX_PAGES; ++i) {
        printf("Page Reference: %d\n", pageReferences[i]);
        
        if (!isPagePresent(pageReferences[i], pageTable, PAGE_FRAMES)) {
            // Page fault occurred, replace the oldest page
            int oldestPageIndex = 0;
            for (int j = 1; j < PAGE_FRAMES; ++j) {
                if (pageTable[j] < pageTable[oldestPageIndex]) {
                    oldestPageIndex = j;
                }
            }

            pageTable[oldestPageIndex] = pageReferences[i];
            pageFaults++;
            printf("Page Fault!\n");
        } else {
            printf("Page Hit!\n");
        }

        // Display the contents of the page table after each page reference
        displayPageTable(pageTable, PAGE_FRAMES);
        printf("\n");
    }

    printf("Total Page Faults: %d\n", pageFaults);

    return 0;
}

