#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READERS 3
#define NUM_WRITERS 2

// Shared resource (in this case, a simple counter)
int sharedResource = 0;

// Semaphores
sem_t mutex;          // Controls access to the shared resource
sem_t readCountMutex;  // Protects the readCount variable
int readCount = 0;     // Number of readers currently accessing the resource

// Writer thread function
void* writer(void* writerID) {
    int id = *(int*)writerID;
    
    // Writing to the shared resource
    printf("Writer %d is waiting to write.\n", id);
    
    // Wait for exclusive access to the shared resource
    sem_wait(&mutex);

    // Writing to the shared resource (critical section)
    sharedResource++;
    printf("Writer %d wrote: %d\n", id, sharedResource);

    // Release the lock
    sem_post(&mutex);

    // Exit the thread
    pthread_exit(NULL);
}

// Reader thread function
void* reader(void* readerID) {
    int id = *(int*)readerID;
    
    // Reading from the shared resource
    printf("Reader %d is waiting to read.\n", id);
    
    // Wait for exclusive access to readCount
    sem_wait(&readCountMutex);

    // Update the number of active readers
    readCount++;

    // If the first reader, acquire the lock on the shared resource
    if (readCount == 1) {
        sem_wait(&mutex);
    }

    // Release the lock on readCount
    sem_post(&readCountMutex);

    // Reading from the shared resource (critical section)
    printf("Reader %d read: %d\n", id, sharedResource);

    // Wait for exclusive access to readCount
    sem_wait(&readCountMutex);

    // Update the number of active readers
    readCount--;

    // If the last reader, release the lock on the shared resource
    if (readCount == 0) {
        sem_post(&mutex);
    }

    // Release the lock on readCount
    sem_post(&readCountMutex);

    // Exit the thread
    pthread_exit(NULL);
}

int main() {
    pthread_t readerThreads[NUM_READERS], writerThreads[NUM_WRITERS];
    int readerIDs[NUM_READERS], writerIDs[NUM_WRITERS];

    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&readCountMutex, 0, 1);

    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; ++i) {
        writerIDs[i] = i;
        pthread_create(&writerThreads[i], NULL, writer, (void*)&writerIDs[i]);
    }

    // Create reader threads
    for (int i = 0; i < NUM_READERS; ++i) {
        readerIDs[i] = i;
        pthread_create(&readerThreads[i], NULL, reader, (void*)&readerIDs[i]);
    }

    // Join writer threads
    for (int i = 0; i < NUM_WRITERS; ++i) {
        pthread_join(writerThreads[i], NULL);
    }

    // Join reader threads
    for (int i = 0; i < NUM_READERS; ++i) {
        pthread_join(readerThreads[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&readCountMutex);

    return 0;
}

