# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>

# define NUM_ITERATIONS 1000000

int counter = 0;    // Shared counter variable
pthread_mutex_t lock; // Mutex lock

void* incrementCounter(void* threadid) {
    for (int i=0; i<NUM_ITERATIONS; i++) {
        // Lock the critical section
        // pthread_mutex_lock(&lock);
        counter++;  // Increment the counter
        // pthread_mutex_unlock(&lock);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[2];   // Create two threads

    // Initialize the mutex
    pthread_mutex_init(&lock, NULL);

    // Create the threads
    pthread_create(&threads[0], NULL, incrementCounter, (void*)0);
    pthread_create(&threads[1], NULL, incrementCounter, (void*)0);

    // Wait frot threads to finish
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    // Destroy the mutex
    pthread_mutex_destroy(&lock);

    printf("Final counter value: %d\n", counter);
    return 0;
}