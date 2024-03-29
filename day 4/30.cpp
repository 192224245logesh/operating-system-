#include <stdio.h>
#include <pthread.h>

void *threadFunction(void *arg) {
    printf("Hello from the new thread!\n");
    pthread_exit(NULL);
}

int main() {
    pthread_t myThread1, myThread2;

    // (i) Create two new threads
    pthread_create(&myThread1, NULL, threadFunction, NULL);
    pthread_create(&myThread2, NULL, threadFunction, NULL);

    // (ii) Wait for the first thread to finish
    pthread_join(myThread1, NULL);

    printf("Back in the main thread after the first join.\n");

    // (iii) Check if the threads are equal
    if (pthread_equal(myThread1, myThread2)) {
        printf("The threads are equal.\n");
    } else {
        printf("The threads are not equal.\n");
    }

    // (iv) Exit the main thread
    pthread_exit(NULL);
}

