#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int count = 0; // quantos itens há no buffer

pthread_mutex_t mutex;
sem_t empty; // quantas posições vazias há
sem_t full;  // quantas posições cheias há

void *producer(void *arg) {
    int item;
    while (1) {
        item = rand() % 100; // produz um item aleatório
        sem_wait(&empty);    // espera se o buffer estiver cheio
        pthread_mutex_lock(&mutex);

        buffer[count++] = item;
        printf("Produtor produziu: %d (count = %d)\n", item, count);

        pthread_mutex_unlock(&mutex);
        sem_post(&full);     // avisa que tem um item novo

        sleep(1);
    }
}

void *consumer(void *arg) {
    int item;
    while (1) {
        sem_wait(&full);     // espera se o buffer estiver vazio
        pthread_mutex_lock(&mutex);

        item = buffer[--count];
        printf("Consumidor consumiu: %d (count = %d)\n", item, count);

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);    // avisa que há espaço no buffer

        sleep(2);
    }
}

int main() {
    pthread_t t1, t2;

    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BUFFER_SIZE); // no começo, tudo vazio
    sem_init(&full, 0, 0);            // nenhum item ainda

    pthread_create(&t1, NULL, producer, NULL);
    pthread_create(&t2, NULL, consumer, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
