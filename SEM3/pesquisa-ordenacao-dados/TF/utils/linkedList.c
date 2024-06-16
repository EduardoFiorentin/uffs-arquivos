#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "constants.h"
#include "dict_functions.h"


// iniciar / resetar uma lista para os valores iniciais
void begin_list(List *list) {
    list->begin = NULL; 
    list->size = 0; 
}


// inserção ordenada de novos elementos em lista encadeada 
void insert_sorted_node(List *list, Node *new_node) {

    // se lista vazia - novo nó é o primeiro 
    if (list->begin == NULL) {
        list->begin = new_node;
    }

    // Se a lista tiver elementos, mas o novo elemento precisa ser inserido no início
    // inserir no inicio se a frequencia do antigo primeiro for maior ou se 
    // a frequencia do antigo primeiro for igual a do novo, mas o caractere do novo deve vir antes
    else if (list->begin->frequency > new_node->frequency || 
    (list->begin->frequency == new_node->frequency && (int)list->begin->character > (int)new_node->character)) {
        new_node->next = list->begin;
        list->begin = new_node; 
    }

    // caso o novo nó deva ser inserido no meio da lista ou no final 
    else {
        Node *aux;
        aux = list->begin; 

        // avança até encontrar a posição correta para o novo nó
        while (aux->next != NULL && 
              (aux->next->frequency < new_node->frequency || 
              (aux->next->frequency == new_node->frequency && (int)aux->next->character < (int)new_node->character))) {
            aux = aux->next; 
        }

        // insere o novo nó na posição correta
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

            insert_sorted_node(list, new_node); 
        }
    }
}

void print_list(List *list) {
    Node *aux = list->begin;
    
    printf("\nLista ordenada: Tamanho: %d\n", list->size);
    while (aux != NULL) {

        // se o caractere for um '\0'
        if (aux->character == '\0') {
            printf("\tCaractere: '\\0' - Freq: %d\n", aux->frequency, aux->next == NULL ? 1 : 0);
        }

        // se o caractere for um espaço
        else if (aux->character == ' ') {
            printf("\tCaractere: '_' - Freq: %d\n", aux->frequency);
        }

        else {
            printf("\tCaractere: %c - Freq: %d\n", aux->character, aux->frequency);
        }

        aux = aux->next;
    }
}

// remove e retorna o primeiro nodo da lista encadeada (caso exista)
Node* remove_begin_node(List* list) {
    Node *aux = NULL;

    // passa o primeiro elemento da lista (caso exista) para aux e, então, o remove da lista 
    if (list->begin != NULL) {
        aux = list->begin;
        list->begin = aux->next; 
        aux->next = NULL; 

        list->size--; 
    }

    return aux; 
}