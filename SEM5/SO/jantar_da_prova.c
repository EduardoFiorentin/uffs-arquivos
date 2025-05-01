#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <errno.h>
#include <semaphore.h>
#include <fenv.h>

#define N 5
#define THINKING 0
#define HUNGRY 1
#define EATING 2
int state[N];
sem_t mutex;
sem_t s[N];

int left(int id);
int right(int id);
void *philosopher(void *data);
void take_forks(int id);
void put_forks(int id);
void test(int id);

int main(void) {
    int i;
    pthread_t tids[N];

    sem_init(&mutex, 0, 1); // ? 

    for (i = 0; i<N; i++) { 
        sem_init(&s[i], 0, 0);
        state[i] = THINKING;
    }

    // alocar ponteiro para ids e criar threads
    for (i = 0 ; i < N ; i++) {
        int *j = malloc(sizeof(int));
        *j = i;
        printf("Filosofo criado: %d\n", *j);
        pthread_create(&tids[i], NULL, philosopher, (void*)j);
    } 

    // esperar threads terminarem 
    for (i = 0 ; i < N ; i++) {
        pthread_join(tids[i], NULL);
        printf("Thread id %ld retornou.\n", tids[i]);
    }
}

void* philosopher(void* data) {
    int id = *((int*)data);
    while(1) {
        printf("Filosofo %d está pensando!\n", id);
        sleep(2);
        take_forks(id);
        printf("Filosofo %d está comendo!\n", id);
        sleep(3);
        put_forks(id);
    }
    pthread_exit(NULL);
}

int left(int id) {
    return ((id + N - 1) % N);
}

int right(int id) {
    return ((id + 1) % N);
}

void take_forks(int id) {
    sem_wait(&mutex);
    state[id] = HUNGRY;
    test(id);
    sem_post(&mutex);
    sem_wait(&s[id]);
}

void put_forks(int id) {
    sem_wait(&mutex);
    state[id] = THINKING;
    test(left(id));
    test(right(id));
    sem_post(&mutex);    
}

void test(int id) {
    if (state[id] == HUNGRY
        && state[left(id)] != EATING
        && state[right(id) != EATING])
    {
        state[id] = EATING;
        sem_post(&s[id]);
    }
}