#include "stdio.h"
#include "stdlib.h"
#include "linked_list.c"
#include "util.c"

int main() {

    Tlist* linked_list = NULL; 
    Tlist* vectorList = NULL; 

    printf("Inicio: ");
    printTList(linked_list); 

    int vector[] = {4, 40, 9, 42, 8, 17, 7, 0, 13, 50, 3, 49, 4, 2, 46, 3, 4, 28, 24, 27, 28, 35, 31, 22, 28, 2, 34, 35, 48, 35, 1, 49, 27, 16, 10, 28, 36, 1, 31, 3, 47, 2, 17, 29, 23, 29, 13, 43, 14, 37}; 
    int listSize = sizeof(vector)/sizeof(int);

    linked_list = vectorToNewList(linked_list, vector, listSize); 

    vectorList = listToStructVector(linked_list, listSize); 
    printf("\nValores linked list original: ");
    printTList(linked_list); 
    printf("\n");

    printf("Vetor de structs: ");
    for (int i = 0; i < listSize; i++) printf("%d ", vectorList[i].value);

    linked_list = structVectorToList(linked_list, vectorList, listSize); 

    // linked_list->value = 450; 

    printf("\nValores linked list nova: ");
    printTList(linked_list); 
    
    // bubbleSort(linked_list, listSize);

    // printf("\nDepois da ordenacao: ");
    // printTList(linked_list); 
    // printf("\nValores linked list original: ");
    // printTList(linked_list); 
    printf("\n");

    freeList(linked_list);

    return 0; 
}