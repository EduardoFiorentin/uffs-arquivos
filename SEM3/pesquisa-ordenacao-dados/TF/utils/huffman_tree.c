#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "constants.h"
#include "dict_functions.h"
#include "linked_list.h"

// monta e retorna uma árvore de huffman com os nodos da lista passada 
Node* assemble_huffman_tree(List* list) {
    
    Node *first, *second, *new_node; 

    while (list->size > 1) {
        first = remove_begin_node(list); 
        second = remove_begin_node(list); 

        new_node = (Node*) malloc(sizeof(Node)); 

        new_node->character = '\0'; 
        new_node->frequency = first->frequency + second->frequency;
        new_node->left = first;
        new_node->right = second; 
        new_node->next = NULL; 
        
        insert_sorted_node(list, new_node); 
    }

    return list->begin; 
}