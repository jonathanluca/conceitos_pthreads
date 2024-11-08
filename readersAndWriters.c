#include <pthread.h>
#include <stdio.h>

pthread_mutex_t resource_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t reader_count_mutex = PTHREAD_MUTEX_INITIALIZER;
int reader_count = 0;

void *reader(void *arg) {
    pthread_mutex_lock(&reader_count_mutex);
    reader_count++;
    if (reader_count == 1)
        pthread_mutex_lock(&resource_mutex);
    pthread_mutex_unlock(&reader_count_mutex);

    // Seção crítica de leitura
    printf("Leitor %d está lendo\n", *(int *)arg);

    pthread_mutex_lock(&reader_count_mutex);
    reader_count--;
    if (reader_count == 0)
        pthread_mutex_unlock(&resource_mutex);
    pthread_mutex_unlock(&reader_count_mutex);

    return NULL;
}

void *writer(void *arg) {
    pthread_mutex_lock(&resource_mutex);

    // Seção crítica de escrita
    printf("Escritor %d está escrevendo\n", *(int *)arg);

    pthread_mutex_unlock(&resource_mutex);
    return NULL;
}

int main() {
    pthread_t readers[5], writers[5];
    int ids[5] = {1, 2, 3, 4, 5};

    int i;
    // Criação de threads de leitores e escritores
    for (i = 0; i < 5; i++) {
        pthread_create(&readers[i], NULL, reader, &ids[i]);
        pthread_create(&writers[i], NULL, writer, &ids[i]);
    }

    // Aguarda o término das threads
    for (i = 0; i < 5; i++) {
        pthread_join(readers[i], NULL);
        pthread_join(writers[i], NULL);
    }

    return 0;
}
