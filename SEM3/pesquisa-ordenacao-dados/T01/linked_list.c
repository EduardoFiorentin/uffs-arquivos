#include "stdio.h"
#include "stdlib.h"

//tipos 
typedef struct tlist
{
    int value; 
    struct tlist* next; 
} Tlist;

Tlist* insertNode(Tlist* list, int newValue);
Tlist* vectorToNewList(Tlist* list, int* vector, int vectorSize);
Tlist* listToStructVector(Tlist* list, int listSize);
Tlist* structVectorToList(Tlist* vector, int listSize);
void printTList(Tlist* list);
void freeList(Tlist* list);


// cria nodo no final da lista  
Tlist* insertNode(Tlist* list, int newValue) {
    
    // criar novo nodo 
    Tlist* newNode; 
    newNode = (Tlist*) malloc(sizeof(Tlist));

    newNode->next = NULL;
    newNode->value = newValue; 

    // inserir nodo
        // se a lista estiver vazia, o nodo se torna a raiz da lista 
        // se não é inserido no final
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

// insere todos os elementos de um vetor de inteiros no final de uma lista encadeada, criando novos nodos
Tlist* vectorToNewList(Tlist* list, int* vector, int vectorSize) {
    for (int i = 0; i < vectorSize; i++) {
        list = insertNode(list, vector[i]); 
    }
    return list; 
}


// transforma uma lista encadeada em um vetor do tipo Tlist
Tlist* listToStructVector(Tlist* list, int listSize) {
    Tlist *vector = (Tlist*) malloc(sizeof(Tlist) * listSize);
    Tlist *aux = list; 

    int i = 0; 
    for(; aux != NULL; aux = aux->next, i++) {
        vector[i] = *aux;
    }

    return vector;
}

// transforma um vetor de nodos de struct do tipo TList em uma lista encadeada 
Tlist* structVectorToList(Tlist* vector, int listSize) {

    Tlist *newList = NULL; 

    // nova lista com os valores ordenados 
    for(int i = 0; i < listSize; i++) {
        printf("\nvalor: ", vector[i].value);
        newList = insertNode(newList, vector[i].value);
    }

    return newList; 

}

// imprime o parametro value dos nodos da lista encadeada 
void printTList(Tlist* list) {
    Tlist* aux = list; 
    if (aux == NULL) {
        printf("Lista vazia..."); 
        return; 
    }

    while (aux != NULL) {
        printf("%d ", aux->value);
        aux = aux->next;
    }
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
