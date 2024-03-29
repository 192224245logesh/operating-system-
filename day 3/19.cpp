#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 2
#define ITERATIONS 1000000

// Shared resource
int counter = 0;

// Mutex lock
pthread_mutex_t mutex;

// Function to increment the counter
void* incrementCounter(void* threadID) {
    for (int i = 0; i < ITERATIONS; ++i) {
        // Acquire the mutex lock before accessing the shared resource
        pthread_mutex_lock(&mutex);

        // Critical section: Accessing the shared resource (counter)
        counter++;

        // Release the mutex lock after accessing the shared resource
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];

    // Initialize the mutex
    pthread_mutex_init(&mutex, NULL);

    // Create two threads
    for (long i = 0; i < NUM_THREADS; ++i) {
        int result = pthread_create(&threads[i], NULL, incrementCounter, (void*)i);

        if (result) {
            fprintf(stderr, "Error creating thread %ld. Code: %d\n", i, result);
            exit(-1);
        }
    }

    // Wait for the threads to finish
    for (long i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    // Destroy the mutex
    pthread_mutex_destroy(&mutex);

    // Print the final value of the counter
    printf("Final Counter Value: %d\n", counter);

    return 0;
}

