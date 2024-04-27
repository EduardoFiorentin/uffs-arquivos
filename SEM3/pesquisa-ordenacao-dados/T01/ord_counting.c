#include "stdio.h"
#include "stdlib.h"
#include "linked_list.c"

// método de ordenação counting sort
Tlist* countingSort(Tlist* list, int listSize) {

    // Cria vetor com os nodos da lista encadeada 
    Tlist* vector = listToStructVector(list, listSize);

    int k = -1; 
    for (int i = 0; i < listSize; i++) if (vector[i].value > k) k = vector[i].value;

    // inicia vetor count 
    int* count;
    count = (int*) malloc((k * sizeof(int)) + 1);

    // resetar vetor count 
    for (int i = 0; i <= k; i++) count[i] = 0; 

    // inicia vetor aux 
    Tlist* aux;
    aux = (Tlist*) malloc(listSize * sizeof(Tlist)); 

    // incrementa o contador 
    for (int i = 0; i < listSize; i++) count[vector[i].value]++; 

    // faz soma acumulada 
    for (int i = 1; i <= k; i++) count[i] += count[i-1]; 

    // insere valores ordenados em aux 
    for (int i = listSize-1; i >= 0; i--) {
        count[vector[i].value] = count[vector[i].value] - 1; 
        aux[count[vector[i].value]] = vector[i]; 
    }

    // transforma o vetor ordenado novamente em uma lista encadeada
    Tlist* sortedList = tListVectorToList(aux, listSize); 

    free(vector);
    free(aux); 
    free(count); 

    return sortedList; 

}

int main() {

    Tlist* linkedList = NULL; 

    // imprimir lista encadeada 
    printf("Inicio: ");
    printTList(linkedList); 

    int vector[] = {1, 1, 5, 4, 11, 10, 10, 2, 4, 5, 12, 7, 15, 11, 10, 7, 9, 5, 15, 14, 0, 0, 15, 8, 1, 9, 0, 5, 13, 8, 2, 13, 14, 1, 10, 4, 11, 3, 5, 5, 9, 7, 13, 7, 0, 11, 3, 6, 0, 6}; 
    int listSize = sizeof(vector)/sizeof(int);

    // cria uma nova lista encadeada a partir dos valores passado em "vector"
    linkedList = vectorToNewList(linkedList, vector, listSize); 

    printf("\nAntes da ordenacao: ");
    printTList(linkedList); 
    
    // ordena a lista encadeada
        // na ordenação, a lista será transformada em um vetor, ordenada e transformada novamente em lista encadeada 
        // uma nova lista odenada será retornada pela função 
    Tlist* sorted_list = countingSort(linkedList, listSize);

    // libera memória alocada para a lista inicial 
    freeList(linkedList);

    printf("\nDepois da ordenacao: ");
    printTList(sorted_list); 

    // libera memória alocada para a lista ordenada 
    freeList(sorted_list);

    return 0; 
}