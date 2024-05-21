#include <stdio.h>
#include <stdlib.h>

// definir tipos e funções usadas para manipulação das listas encadeadas 
typedef struct tlist
{
    int value; 
    struct tlist* next; 
} Tlist;

Tlist* insertNode(Tlist* list, int newValue);
void printTList(Tlist* list);
void freeList(Tlist* list);