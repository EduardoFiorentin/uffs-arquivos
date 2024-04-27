#include "stdio.h"
#include "stdlib.h"
#include "linked_list.c"


// troca os valores duas posições do vetor
void swap (Tlist *vector, int i, int j) {
    Tlist ref = vector[i];
    vector[i] = vector[j];
    vector[j] = ref;
}

Tlist* bubbleSort(Tlist *list, int listSize) {

    // Cria vetor com os nodos da lista encadeada 
    Tlist* vector = listToStructVector(list, listSize);

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
                swap(vector, j, j+1); 
            }
            j++;
        }
        if (!change) break;
        i--;
    }


    // transforma o vetor ordenado novamente em uma lista encadeada

    Tlist* sortedList = tListVectorToList(vector, listSize); 
    free(vector); 

    return sortedList;
}

int main() {

    Tlist* linkedList = NULL; 

    // imprimir lista encadeada 
    printf("Inicio: ");
    printTList(linkedList); 

    int vector[] = {4, 40, 9, 42, 8, 17, 7, 0, 13, 50, 3, 49, 4, 2, 46, 3, 4, 28, 24, 27, 28, 35, 31, 22, 28, 2, 34, 35, 48, 35, 1, 49, 27, 16, 10, 28, 36, 1, 31, 3, 47, 2, 17, 29, 23, 29, 13, 43, 14, 37}; 

    int listSize = sizeof(vector)/sizeof(int);

    // cria uma nova lista encadeada a partir dos valores passado em "vector"
    linkedList = vectorToNewList(linkedList, vector, listSize); 

    printf("\nAntes da ordenacao: ");
    printTList(linkedList); 
    
    // ordena a lista encadeada
    Tlist* sortedList = bubbleSort(linkedList, listSize);
    
    // libera memória alocada para a lista inicial 
    freeList(linkedList);

    printf("\nDepois da ordenacao: ");
    printTList(sortedList); 

    // libera memória alocada para a lista encadeada 
    freeList(sortedList);

    return 0; 
}
