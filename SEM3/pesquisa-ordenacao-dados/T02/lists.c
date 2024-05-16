#include "stdio.h"
#include "stdlib.h"
#include "lists.h"

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

// imprime o parametro value dos nodos da lista encadeada 
void printTList(Tlist* list) {
    Tlist* aux = list; 
    if (aux == NULL) {
        printf(" ."); 
        return; 
    }

    while (aux != NULL) {
        printf("\t%d ", aux->value);
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
