#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "constants.h"
#include "dict_functions.c"

typedef struct node {
    char character; 
    int frequency; 
    struct node *left, *right, *next; 
} Node; 

typedef struct list 
{
    Node* begin; 
    int size; 
} List;

// iniciar / resetar uma lista para os valores iniciais
void begin_list(List *list) {
    list->begin = NULL; 
    list->size = 0; 
}

// inserção ordenada de novos elementos em lista encadeada 
void insert(List *list, Node *new_node) {

    // se lista vazia - novo nó é o primeiro 
    if (list->begin == NULL) {
        list->begin = new_node;
    }

    // Se a lista tiver elementos, mas o novo elemento precisa ser inserido no início
    else if (list->begin->frequency >= new_node->frequency) {
        new_node->next = list->begin;
        list->begin = new_node; 
    }

    // caso o novo nó deva ser inserido no meio da lista
    else {
        Node *aux;
        aux = list->begin; 
        while ( aux->next != NULL && aux->next->frequency < new_node->frequency ) {
            aux = aux->next; 
        }

        // caso de inserção no meio ou final da lista
        new_node->next = aux->next;
        aux->next = new_node; 
    }
    list->size++; 

}

// Função de preenchimento da lista encadeada com os valores da tabela de frequência
// Cria os novos nodos e os insere na lista de forma ordenada 
void fill_list(List *list, int freq_table[], const char dict_chars[]) {
    for (int i = 0; i < SIZE; i++) {

        // se houver incidência do caractere, cria um nodo para ele e o insere na lista encadeada
        if (freq_table[i] > 0) {
            Node *new_node = (Node*)malloc(sizeof(Node));
            new_node->character = dict_chars[i];
            new_node->frequency = freq_table[i];
            new_node->left = NULL;
            new_node->right = NULL; 
            new_node->next = NULL; 

            insert(list, new_node); 
        }
    }
}

void print_list(List *list) {
    Node *aux = list->begin;
    
    printf("\nLista ordenada: Tamanho: %d\n", list->size);
    while (aux != NULL) {
        printf("\tCaractere: %c - Freq: %d\n", aux->character, aux->frequency);
        aux = aux->next;
    }
}