#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>

// Definindo os dois mutexes compartilhados
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

// Função que será executada pela primeira thread
void* thread1_func(void* arg) {
    printf("Thread 1: Tentando bloquear mutex1...\n");
    pthread_mutex_lock(&mutex1);
    printf("Thread 1: Mutex1 bloqueado.\n");

    // Simula algum trabalho com o mutex1
    Sleep(1);

    printf("Thread 1: Tentando bloquear mutex2...\n");
    pthread_mutex_lock(&mutex2);
    printf("Thread 1: Mutex2 bloqueado.\n");

    // Libera os mutexes
    pthread_mutex_unlock(&mutex2);
    pthread_mutex_unlock(&mutex1);

    return NULL;
}

// Função que será executada pela segunda thread
void* thread2_func(void* arg) {
    printf("Thread 2: Tentando bloquear mutex2...\n");
    pthread_mutex_lock(&mutex2);
    printf("Thread 2: Mutex2 bloqueado.\n");

    // Simula algum trabalho com o mutex2
    Sleep(1);

    printf("Thread 2: Tentando bloquear mutex1...\n");
    pthread_mutex_lock(&mutex1);
    printf("Thread 2: Mutex1 bloqueado.\n");

    // Libera os mutexes
    pthread_mutex_unlock(&mutex1);
    pthread_mutex_unlock(&mutex2);

    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Cria as threads
    if (pthread_create(&thread1, NULL, thread1_func, NULL)) {
        printf("Erro ao criar a Thread 1\n");
        return 1;
    }
    if (pthread_create(&thread2, NULL, thread2_func, NULL)) {
        printf("Erro ao criar a Thread 2\n");
        return 1;
    }

    // Aguarda as threads terminarem (isso nunca acontece devido ao deadlock)
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Destrói os mutexes
    pthread_mutex_destroy(&mutex1);
    pthread_mutex_destroy(&mutex2);

    return 0;
}
