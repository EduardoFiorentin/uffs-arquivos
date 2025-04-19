#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N 5  // número de filósofos

pthread_mutex_t garfos[N];

void pensar(int id) {
    printf("Filosofo %d esta pensando...\n", id);
    sleep(rand() % 3 + 1);
}

void comer(int id) {
    printf("Filosofo %d esta comendo\n", id);
    sleep(rand() % 2 + 1);
}

void* filosofo(void* num) {
    int id = *(int*)num;

    while (1) {
        pensar(id);

        // Pegar os garfos
        int garfo_esq = id;
        int garfo_dir = (id + 1) % N;

        // Estratégia: pegar sempre o menor índice primeiro para evitar deadlock
        if (id % 2 == 0) {
            pthread_mutex_lock(&garfos[garfo_esq]);
            pthread_mutex_lock(&garfos[garfo_dir]);
        } else {
            pthread_mutex_lock(&garfos[garfo_dir]);
            pthread_mutex_lock(&garfos[garfo_esq]);
        }

        comer(id);

        // Devolver os garfos
        pthread_mutex_unlock(&garfos[garfo_esq]);
        pthread_mutex_unlock(&garfos[garfo_dir]);

        printf("Filosofo %d terminou de comer e largou os garfos.\n", id);
    }
    return NULL;
}

int main() {
    pthread_t threads[N];
    int ids[N];

    srand(time(NULL));

    for (int i = 0; i < N; i++)
        pthread_mutex_init(&garfos[i], NULL);

    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, filosofo, &ids[i]);
    }

    for (int i = 0; i < N; i++)
        pthread_join(threads[i], NULL);

    for (int i = 0; i < N; i++)
        pthread_mutex_destroy(&garfos[i]);

    return 0;
}
