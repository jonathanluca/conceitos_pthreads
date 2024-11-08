#include <pthread.h>
#include <stdio.h>

#define THREADS 5

pthread_barrier_t barrier;

void *thread_func(void *arg) {
    int id = *(int *)arg;
    printf("Thread %d chegou na barreira\n", id);
    pthread_barrier_wait(&barrier);
    printf("Thread %d passou pela barreira\n", id);
    return NULL;
}

int main() {
    pthread_t threads[THREADS];
    int ids[THREADS];

    pthread_barrier_init(&barrier, NULL, THREADS);

    int i;
    for (i = 0; i < THREADS; i++) {
        ids[i] = i + 1;
        pthread_create(&threads[i], NULL, thread_func, &ids[i]);
    }

    for (i = 0; i < THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_barrier_destroy(&barrier);

    return 0;
}
