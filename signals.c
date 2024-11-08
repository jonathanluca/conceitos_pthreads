#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>

// Definindo a variável de condição e o mutex
pthread_mutex_t lock;
pthread_cond_t signal_condition;

// Função que será executada pela primeira thread
void* thread1_func(void* arg) {
    printf("Thread 1: Iniciando execução...\n");

    // Simula algum processamento
    Sleep(1);

    // Bloqueia o mutex antes de sinalizar
    pthread_mutex_lock(&lock);
    printf("Thread 1: Preparando para enviar o sinal...\n");

    // Sinaliza a variável de condição para liberar a thread 2
    pthread_cond_signal(&signal_condition);

    // Libera o mutex
    pthread_mutex_unlock(&lock);

    return NULL;
}

// Função que será executada pela segunda thread
void* thread2_func(void* arg) {
    printf("Thread 2: Aguardando o sinal...\n");

    // Bloqueia o mutex e espera o sinal
    pthread_mutex_lock(&lock);

    // Espera o sinal da thread 1
    pthread_cond_wait(&signal_condition, &lock);

    printf("Thread 2: Recebeu o sinal! Continuando execução...\n");

    // Libera o mutex
    pthread_mutex_unlock(&lock);

    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Inicializando o mutex e a variável de condição
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&signal_condition, NULL);

    // Criação das threads
    if (pthread_create(&thread1, NULL, thread1_func, NULL)) {
        printf("Erro ao criar a Thread 1\n");
        return 1;
    }
    if (pthread_create(&thread2, NULL, thread2_func, NULL)) {
        printf("Erro ao criar a Thread 2\n");
        return 1;
    }

    // Aguardar a conclusão das threads
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Destruir o mutex e a variável de condição
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&signal_condition);

    return 0;
}
