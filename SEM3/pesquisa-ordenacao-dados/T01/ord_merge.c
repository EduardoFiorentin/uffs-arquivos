#include "stdio.h"
#include "stdlib.h"
#include "linked_list.c"
#include "util.c"


void merge(int *A, int start, int mid, int end) {
    int size = end-start+1;
    int* aux = (int*)malloc(sizeof(int) * size);
    
    int i = start;
    int j = mid + 1;
    int k = 0; 

    while (i <= mid && j <= end) {
        if (A[i] <= A[j]) {
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

void mergeSortAux(int* A, int inicio, int fim) {
    if (inicio < fim) {
        int meio;
        meio = (int)(inicio + fim)/2;

        mergeSortAux(A, inicio, meio);
        mergeSortAux(A, meio + 1, fim);
        merge(A, inicio, meio, fim); 
    }
}

void mergeSort(Tlist* list, int listSize) {
    int* vector = listToVector(list, listSize);
    mergeSortAux(vector, 0, listSize);
    sortedVectorToList(list, vector, listSize); 
    free(vector); 
}

int main() {

    Tlist* linked_list = NULL; 

    printf("Inicio: ");
    printTList(linked_list); 

    int vector[] = {29, 8, 41, 11, 20, 6, 4, 6, 47, 29, 15, 6, 50, 17, 16, 49, 26, 50, 31, 5, 39, 2, 28, 12, 17, 6, 5, 39, 50, 10, 4, 14, 31, 44, 6, 48, 35, 48, 27, 5, 5, 39, 23, 37, 49, 22, 25, 20, 17, 40}; 
    int listSize = sizeof(vector)/sizeof(int);
    linked_list = vectorToNewList(linked_list, vector, listSize); 

    printf("\nAntes da ordenacao: ");
    printTList(linked_list); 
    
    mergeSort(linked_list, listSize);

    printf("\nDepois da ordenacao: ");
    printTList(linked_list); 

    freeList(linked_list);

    return 0; 
}