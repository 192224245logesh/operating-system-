#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> // Include for usleep function

#define BUFFER_SIZE 5

// Buffer and semaphore declarations
int buffer[BUFFER_SIZE];
sem_t empty, full, mutex;

// Function prototypes
void *producer(void *arg);
void *consumer(void *arg);

int main() {
    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    // Create threads for producer and consumer
    pthread_t producerThread, consumerThread;

    pthread_create(&producerThread, NULL, producer, NULL);
    pthread_create(&consumerThread, NULL, consumer, NULL);

    // Join threads
    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);

    // Destroy semaphores
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}

void *producer(void *arg) {
    int item = 0;

    while (1) {
        // Wait for empty buffer
        sem_wait(&empty);

        // Wait for mutex
        sem_wait(&mutex);

        // Produce item and add to buffer
        buffer[item % BUFFER_SIZE] = item;
        printf("Produced item %d\n", item);

        // Release mutex
        sem_post(&mutex);

        // Signal that buffer is full
        sem_post(&full);

        // Increment item for the next iteration
        item++;

        // Sleep for some time to simulate production time
        usleep(100000); // Sleep for 100 milliseconds
    }
}

void *consumer(void *arg) {
    int item;

    while (1) {
        // Wait for full buffer
        sem_wait(&full);

        // Wait for mutex
        sem_wait(&mutex);

        // Consume item from buffer
        item = buffer[item % BUFFER_SIZE];
        printf("Consumed item %d\n", item);

        // Release mutex
        sem_post(&mutex);

        // Signal that buffer is empty
        sem_post(&empty);

        // Increment item for the next iteration
        item++;

        // Sleep for some time to simulate consumption time
        usleep(150000); // Sleep for 150 milliseconds
    }
}

