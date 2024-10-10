#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 5

void* printHello(void* threadid) {
    long tid = (long)threadid;
    printf("Hello World from thread %ld\n", tid);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    for (long t = 0; t < NUM_THREADS; t++) {
        int rc = pthread_create(&threads[t], NULL, printHello, (void*)t);
        if (rc) {
            printf("Error: unable to create thread, %d\n", rc);
            exit(-1);
        }
    }
    for (int t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }
    return 0;
}
