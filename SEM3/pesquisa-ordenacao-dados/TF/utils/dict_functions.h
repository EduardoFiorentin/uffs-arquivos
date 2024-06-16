#pragma once 

int get_dict_position(char c); 
char** dict_aloc(int size);
void fill_dict(char **dict, Node *root, const char *path, int size);
void print_dict(char **dict);
