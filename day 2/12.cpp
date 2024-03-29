#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t chopstick[NUM_PHILOSOPHERS];

void *philosopher(void *arg) {
    int philosopher_id = *((int *)arg);
    int left_chopstick = philosopher_id;
    int right_chopstick = (philosopher_id + 1) % NUM_PHILOSOPHERS;

    while (1) {
        // Think
        printf("Philosopher %d is thinking\n", philosopher_id);
        usleep(1000000); // Sleep for 1 second

        // Pick up left chopstick
        pthread_mutex_lock(&chopstick[left_chopstick]);
        printf("Philosopher %d picked up left chopstick %d\n", philosopher_id, left_chopstick);

        // Pick up right chopstick
        pthread_mutex_lock(&chopstick[right_chopstick]);
        printf("Philosopher %d picked up right chopstick %d\n", philosopher_id, right_chopstick);

        // Eat
        printf("Philosopher %d is eating\n", philosopher_id);
        usleep(1000000); // Sleep for 1 second

        // Put down right chopstick
        pthread_mutex_unlock(&chopstick[right_chopstick]);
        printf("Philosopher %d put down right chopstick %d\n", philosopher_id, right_chopstick);

        // Put down left chopstick
        pthread_mutex_unlock(&chopstick[left_chopstick]);
        printf("Philosopher %d put down left chopstick %d\n", philosopher_id, left_chopstick);
    }
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];

    // Initialize mutexes for chopsticks
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        pthread_mutex_init(&chopstick[i], NULL);
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        philosopher_ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
    }

    // Wait for philosopher threads to finish (which will never happen in this case)
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy mutexes
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        pthread_mutex_destroy(&chopstick[i]);
    }

    return 0;
}

