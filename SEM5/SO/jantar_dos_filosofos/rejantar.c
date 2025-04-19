#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N 5

// definir N mutexes
pthread_mutex_t forks[N];

void spend_some_time() {
    sleep(rand() % 3 + 1);
}

void think(int id) {
    printf("Filosofo %d esta pensando!\n", id);
    spend_some_time();
}

void eat(int id) {
    printf("Filosofo %d esta comendo!\n", id);
    spend_some_time();
}

void* philosopher(void* num) {

    int id = *(int*) num;

    while(1) {

        think(id);

        // escolher 
        int left_fork = id;
        int right_fork = (id + 1) % N;

        pthread_mutex_lock(&forks[left_fork]);
        pthread_mutex_lock(&forks[right_fork]);

        eat(id);

        pthread_mutex_unlock(&forks[left_fork]);
        pthread_mutex_unlock(&forks[right_fork]);

        printf("Filosofo %d terminou de comer\n", id);
    }

    return NULL;

}


int main() {

    pthread_t threads[N];
    int ids[N]; 

    srand(time(NULL));

    // iniciar mutex
    for (int i = 0; i < N; i++) 
        pthread_mutex_init(&forks[i], NULL);


    // criar threads
    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, philosopher, &ids[i]);
    }

    // esperar threads terminarem
    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    // finalizar mutex
    for (int i = 0; i < N; i++) 
        pthread_mutex_destroy(&forks[i]); 

    return 0;
}