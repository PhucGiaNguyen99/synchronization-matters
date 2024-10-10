#include <pthread.h>
# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>

# define BUFFER_SIZE 7

int buffer[BUFFER_SIZE];    // Shared buffer
int in = 0; // Producer index
int out = 0; // Consumer index

sem_t full; // semaphore to count the number of full slots in the buffer
sem_t empty;    // semaphore to count the number of empty slots in the buffer

pthread_mutex_t mutex;  // mutext to protect the shared buffer

void* producer(void* arg) {
    int item;
    for (int i=0; i<10; i++) {
        // Produce 10 times
        item = i;   // Produce an item
        sem_wait(&empty);   // wait if buffer is full

        pthread_mutex_lock(&mutex); // Lock the buffer

        // Critical section: add item to buffer
        buffer[in] = item;
        printf("Produced: %d\n", item);
        in = (in+1)%BUFFER_SIZE;    // Update the producer index

        pthread_mutex_unlock(&mutex);   // Unlock the buffer
        sem_post(&full); // Signal that there is one more full slot
    }
    pthread_exit(NULL);
}

void* consumer(void* arg) {
    int item;
    for (int i=0;i<10;i++) {
        // Consume 10 items
        sem_wait(&full);    // Wait if buffer is empty
        pthread_mutex_lock(&mutex); // Lock the buffer

        item=buffer[out];
        printf("Consumed: %d\n", item);
        out = (out+1)%BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);   // Signal that there is one more empty slot 
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t prod1, prod2, cons;

    // Initialize semaphores and mutex
    sem_init(&full, 0, 0);  // Initialize the value of full slots to 0
    sem_init(&empty, 0, BUFFER_SIZE);   // Initialize the value of empty slots to BUFFER_SIZE
    pthread_mutex_init(&mutex, NULL);

    // Create the producer and consumer threads
    pthread_create(&prod1, NULL, producer, NULL);
    pthread_create(&prod2, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    // Wait for both threads to finish
    pthread_join(prod1, NULL);
    pthread_join(prod2, NULL);
    pthread_join(cons, NULL);

    // Destroy the semaphores and mutex
    sem_destroy(&full);
    sem_destroy(&empty);
    pthread_mutex_destroy(&mutex);

    return 0;
}