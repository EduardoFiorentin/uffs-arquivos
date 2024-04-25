#include "stdio.h"
#include "stdlib.h"
#include "linked_list.c"


void merge(Tlist *A, int start, int mid, int end) {
    int size = end-start+1;
    Tlist* aux = (Tlist*)malloc(sizeof(Tlist) * size);
    
    int i = start;
    int j = mid + 1;
    int k = 0; 

    while (i <= mid && j <= end) {
        if (A[i].value <= A[j].value) {
            aux[k] = A[i];
            i++;
        } 
        else {
            aux[k] = A[j];
            j++;
        }
        k++;
    }
    while (i <= mid) {
        aux[k] = A[i];
        k++;
        i++;
    }
    while (j <= end) {
        aux[k] = A[j];
        k++;
        j++;
    }

    for (k = start; k <= end; k++) {
        A[k] = aux[k-start]; 
    }
    free(aux);
}

// merge sort 
void mergeSortAux(Tlist* A, int inicio, int fim) {
    if (inicio < fim) {
        int meio;
        meio = (int)(inicio + fim)/2;

        mergeSortAux(A, inicio, meio);
        mergeSortAux(A, meio + 1, fim);
        merge(A, inicio, meio, fim); 
    }
}


// função de chamada do merge sort 
void mergeSort(Tlist* list, int listSize) {

    // Cria vetor com os nodos da lista encadeada 
    Tlist* vector = listToStructVector(list, listSize);

    mergeSortAux(vector, 0, listSize-1);

    // transforma o vetor ordenado novamente em uma lista encadeada
    list = structVectorToList(list, vector, listSize); 
}

int main() {

    Tlist* linked_list = NULL; 

    // imprimir lista encadeada 
    printf("Inicio: ");
    printTList(linked_list); 

    int vector[] = {24, 30, 19, 38, 19, 31, 11, 12, 27, 34, 1, 37, 43, 17, 1, 28, 36, 31, 45, 27, 4, 48, 23, 46, 36, 31, 41, 37, 33, 6, 24, 10, 43, 23, 12, 4, 18, 24, 25, 7, 48, 15, 29, 45, 0, 8, 32, 12, 19, 6}; 
    int listSize = sizeof(vector)/sizeof(int);

    // cria uma nova lista encadeada a partir dos valores passado em "vector"

    linked_list = vectorToNewList(linked_list, vector, listSize); 

    printf("\nAntes da ordenacao: ");
    printTList(linked_list); 

    // cria uma nova lista encadeada a partir dos valores passado em "vector"
    mergeSort(linked_list, listSize);

    printf("\nDepois da ordenacao: ");
    printTList(linked_list); 

    // libera memória alocada para a lista encadeada 
    freeList(linked_list);

    return 0; 
}