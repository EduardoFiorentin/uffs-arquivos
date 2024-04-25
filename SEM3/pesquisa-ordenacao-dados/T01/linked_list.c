#include "stdio.h"
#include "stdlib.h"


//tipos 
typedef struct tlist
{
    int value; 
    struct tlist* next; 
} Tlist;



// cria nodo no final da lista  
Tlist* insertNode(Tlist* list, int newValue) {
    
    // criar novo nodo 
    Tlist* newNode; 
    newNode = (Tlist*) malloc(sizeof(Tlist));

    newNode->next = NULL;
    newNode->value = newValue; 

    // inserir nodo
        // se a lista estiver vazia, o vetor se torna a raiz da lista 
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
Tlist* structVectorToList(Tlist* list, Tlist* vector, int listSize) {

    // copia o primeiro elemento ordenado para o endereço original 
    // da lista encadeada, mantendo o primeiro elemento da lista 
    // no mesmo endereço de memória
    *list = vector[0]; 
    
    Tlist *aux; 
    aux = list;


    // atualiza os parametros next de cada nodo para o próximo elemento do vetor
    // mantém os nodos no local de memória correspondente ao vetor, mas os trata como lista encadeada
    for(int i = 1; i < listSize; i++) {
        aux->next = &vector[i]; 
        aux = aux->next;
    }
    
    // setar next do último elemento como null
    aux->next = NULL; 

    return list; 

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
        printf("\n%d", aux->value);
        aux = list; 
        list = list->next;
        free(aux); 
    }
}
