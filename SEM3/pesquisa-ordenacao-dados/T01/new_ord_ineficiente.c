#include "stdio.h"
#include "stdlib.h"
#include "linked_list.c"
#include "util.c"

Tlist* bubbleSort(Tlist *list, int listSize) {
    // int* vector = listToVector(list, listSize);
    Tlist* vector = listToStructVector(list, listSize);

    // printf("\nendereco list buble antes: %x ", &list);
    printf("\nVetor de structs: ");
    for (int i = 0; i < listSize; i++) printf("%d ", vector[i].value);

    // bubble está quebrado 

    int i = listSize - 1;
    int j = 0;  
    int change; 
    while (i >= 1) {
        change = 0; 
        j = 0; 
        while(j <= i-1) {
            if (vector[j].value > vector[j+1].value) {
                change = 1;
                swap(vector, i, j); 
            }
            j++;
        }
        if (!change) break;
        i--;
    }
    // sortedVectorToList(list, vector, listSize);

    printf("\nVector after ordenating: ");
    for (int i = 0; i < listSize; i++) printf("%d, ", vector[i].value); 

    list = structVectorToList(list, vector, listSize);
    // free(vector); 

    printf("\nPrimeiro valor: %d\n\n", list->value); 
    // printf("\nSegundo valor: %d\n\n", list->next->value); 

    // printf("\nendereco list buble final: %x ", &list);
    // printTList(list); 
    return list;

}

int main() {

    Tlist* linked_list = NULL; 

    printf("Inicio: ");
    printTList(linked_list); 
    // printf("\nendereco list linked antes: %x ", &linked_list);

    int vector[] = {4, 40, 9, 42, 8, 17, 7, 0, 13, 50, 3, 49, 4, 2, 46, 3, 4, 28, 24, 27, 28, 35, 31, 22, 28, 2, 34, 35, 48, 35, 1, 49, 27, 16, 10, 28, 36, 1, 31, 3, 47, 2, 17, 29, 23, 29, 13, 43, 14, 37}; 
    int listSize = sizeof(vector)/sizeof(int);
    linked_list = vectorToNewList(linked_list, vector, listSize); 

    printf("\nAntes da ordenacao: ");
    printTList(linked_list); 
    
    linked_list = bubbleSort(linked_list, listSize);

    // printf("\nendereco list linked depois: %x ", &linked_list);
    printf("\nDepois da ordenacao: ");
    printTList(linked_list); 
    // printf("\nPrimeiro valor: %d", linked_list->value); 

    freeList(linked_list);

    return 0; 
}