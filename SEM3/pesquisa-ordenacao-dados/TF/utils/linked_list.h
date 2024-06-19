#include "constants.h"

void begin_list(List *list); 
void insert_sorted_node(List *list, Node *new_node);
void fill_list(List *list, int freq_table[], const char dict_chars[]);
Node* remove_begin_node(List* list);