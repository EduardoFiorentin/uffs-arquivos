#pragma once

#define SIZE 27

const char DICT_CHARS[] = {' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
const int DICT_POSITION[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26};

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
