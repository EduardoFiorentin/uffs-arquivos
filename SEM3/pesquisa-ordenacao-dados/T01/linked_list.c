#include "stdio.h"
#include "stdlib.h"


//tipos 
typedef struct tlist
{
    int value; 
    struct tlist* next; 
} Tlist;

// declaração de funções

void freeList(Tlist* list);


// insere nodo novo no final da lista  
Tlist* insertNode(Tlist* list, int newValue) {
    
    // criar novo nodo 
    Tlist* newNode; 
    newNode = (Tlist*) malloc(sizeof(Tlist));

    newNode->next = NULL;
    newNode->value = newValue; 

    // inserir nodo
    if (list == NULL) {
        list = newNode;
        return list; 
    } 
    else {
        Tlist* aux = list; 
        while (aux->next != NULL) aux = aux->next; 
        aux->next = newNode; 
        return list; 
    }

}

// inserir todos os elementos de um vetor no final de uma lista encadeada 
Tlist* vectorToNewList(Tlist* list, int* vector, int vectorSize) {
    for (int i = 0; i < vectorSize; i++) {
        list = insertNode(list, vector[i]); 
    }
    return list; 
}

// transfere os valores do vetor ordenado para uma lista existente
    // não cria nodos novos 
void sortedVectorToList(Tlist* list, int* sortedVector, int size) {
    Tlist* aux; 
    int i = 0; 
    for(aux = list; aux != NULL; aux = aux->next, i++) aux->value = sortedVector[i];
}

// passar valores de uma lista para um novo vetor
int* listToVector(Tlist* list, int listSize) {
    int* vector = (int*) malloc(sizeof(int)*listSize);
    Tlist* aux; 

    int i = 0; 
    for(aux = list; aux != NULL; aux = aux->next, i++) vector[i] = aux->value;

    return vector; 
}

// -----------------------------------------------------------------------------

Tlist* listToStructVector(Tlist* list, int listSize) {
    Tlist *vector = (Tlist*) malloc(sizeof(Tlist) * listSize);
    Tlist *aux = list; 

    int i = 0; 
    for(; aux != NULL; aux = aux->next, i++) {
        vector[i] = *aux;
    }

    return vector;
}

Tlist* structVectorToList(Tlist* list, Tlist* vector, int listSize) {
    freeList(list);
    printf("\nPrimeiro do vector[0]: %d", vector[0].value);
    list = &(vector[0]); 
    Tlist* aux; 
    aux = list; 
    
    for(int i = 1; i < listSize; i++) {
        aux->next = &vector[i]; 
        aux = aux->next;
    }
    // aux->next = NULL; 

    return list; 

}

// imprime lista encadeada 
void printTList(Tlist* list) {
    Tlist* aux = list; 
    if (aux == NULL) {
        printf("Lista vazia..."); 
        return; 
    }

    for (; aux != NULL; aux = aux->next) printf("%d ", aux->value); 
}


// liberar meméria alocada para lista encadeada
void freeList(Tlist* list) {
    Tlist* aux; 

    while (list != NULL) {
        aux = list; 
        list = list->next;
        free(aux); 
    }
}
