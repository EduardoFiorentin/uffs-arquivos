#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "constants.h"
#include "dict_functions.h"
#include "linked_list.h"

Node* assemble_huffman_tree(List* list) {
    
    Node *first, *second, *new_node; 

    while (list->size > 1) {
        first = remove_begin_node(list); 
        second = remove_begin_node(list); 

        new_node = (Node*)malloc(sizeof(Node)); 

        new_node->character = '\0'; 
        new_node->frequency = first->frequency + second->frequency;
        new_node->left = first;
        new_node->right = second; 
        new_node->next = NULL; 
        
        insert_sorted_node(list, new_node); 
    }

    return list->begin; 
}

void print_huffman_tree(Node* root, int size) {
    if (root->left == NULL && root->right == NULL) 
        printf("\tFolha: %c\tH: %d\n", root->character, size); 
    
    else {
        print_huffman_tree(root->left, size + 1);
        print_huffman_tree(root->right, size + 1);
    }
}
