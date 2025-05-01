#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> // para sleep()

#define N 5 // número de processos

// implementação de exclusão mútua com espera osciosa baseada em chaveamento obrigatório

pthread_t threads[N];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int turn = 0; // variável compartilhada

void* processo(void* arg) {
    int id = *((int*)arg);
    while (1) {
        // Loop de espera
        while (1) {
            pthread_mutex_lock(&mutex);
            if (turn == id) {
                // se turn == id, é a vez desta thread -> sai do loop de espera
                pthread_mutex_unlock(&mutex);
                break; 
            }
            pthread_mutex_unlock(&mutex);
            usleep(1000); // 1 milissegundo
        }
        
        // inicia processamento 
        printf("[Processo %d] Entrando na região crítica\n", id);
        sleep(1); // Simula trabalho
        printf("[Processo %d] Saindo da região crítica\n", id);

        // Passa a vez para o próximo
        // bloqueia o turn para ninguém mexer até esta thread terminar a atualização
        pthread_mutex_lock(&mutex);
        // região crítica
        turn = (id + 1) % N;
        
        pthread_mutex_unlock(&mutex);

        // Região não crítica
        sleep(1); // Simula trabalho fora da região crítica
    }
    
    return NULL;
}

int main() {
    int ids[N];
    
    // Cria threads
    for (int i = 0; i < N; i++) {
        ids[i] = i;
        if (pthread_create(&threads[i], NULL, processo, (void*)&ids[i]) != 0) {
            perror("Erro ao criar thread");
            exit(1);
        }
    }

    // Espera as threads (na prática, elas rodam para sempre)
    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    
    return 0;
}
