#include <stdio.h>
#include <pthread.h>
#include <unistd.h>  // Include for usleep

// Function to be executed by the first thread
void *threadFunction1(void *arg) {
    for (int i = 1; i <= 5; ++i) {
        printf("Thread 1: Count %d\n", i);
        usleep(500000); // Sleep for 500 milliseconds
    }
    pthread_exit(NULL);
}

// Function to be executed by the second thread
void *threadFunction2(void *arg) {
    for (int i = 1; i <= 5; ++i) {
        printf("Thread 2: Count %d\n", i);
        usleep(700000); // Sleep for 700 milliseconds
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2;

    // Create the first thread
    if (pthread_create(&thread1, NULL, threadFunction1, NULL) != 0) {
        fprintf(stderr, "Error creating thread 1\n");
        return 1;
    }

    // Create the second thread
    if (pthread_create(&thread2, NULL, threadFunction2, NULL) != 0) {
        fprintf(stderr, "Error creating thread 2\n");
        return 1;
    }

    // Wait for the threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Both threads have finished.\n");

    return 0;
}

