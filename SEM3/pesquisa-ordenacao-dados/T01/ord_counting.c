#include "stdio.h"
#include "stdlib.h"
#include "linked_list.c"
#include "util.c"

void countingSort(Tlist* list, int listSize) {
    int* vector = listToVector(list, listSize);

    int k = -1; 
    // encontra o maior
    for (int i = 0; i < listSize; i++) if (vector[i] > k) k = vector[i];

    // inicia vetor count 
    int* count;
    count = (int*) malloc((k * sizeof(int)) + 1);
    for (int i = 0; i <= k; i++) count[i] = 0; 

    // inicia vetor aux 
    int* aux;
    aux = (int*) malloc(listSize * sizeof(int)); 

    // incrementar contador 
    for (int i = 0; i < listSize; i++) count[vector[i]]++; 

    // faz soma acumulada 
    for (int i = 1; i <= k; i++) count[i] += count[i-1]; 

    // inserir valores ordenados em aux 
    for (int i = listSize-1; i >= 0; i--) {
        count[vector[i]] = count[vector[i]] - 1; 
        aux[count[vector[i]]] = vector[i]; 
    }

    copy(aux, vector, listSize); 

    // 
    sortedVectorToList(list, vector, listSize); 

    // limpar vetores auxiliares 
    free(count); 
    free(aux); 
    free(vector); 
}

int main() {

    Tlist* linked_list = NULL; 

    printf("Inicio: ");
    printTList(linked_list); 

    int vector[] = {1, 1, 5, 4, 11, 10, 10, 2, 4, 5, 12, 7, 15, 11, 10, 7, 9, 5, 15, 14, 0, 0, 15, 8, 1, 9, 0, 5, 13, 8, 2, 13, 14, 1, 10, 4, 11, 3, 5, 5, 9, 7, 13, 7, 0, 11, 3, 6, 0, 6}; 
    int listSize = sizeof(vector)/sizeof(int);
    linked_list = vectorToNewList(linked_list, vector, listSize); 

    printf("\nAntes da ordenacao: ");
    printTList(linked_list); 
    
    countingSort(linked_list, listSize);

    printf("\nDepois da ordenacao: ");
    printTList(linked_list); 

    freeList(linked_list);

    return 0; 
}