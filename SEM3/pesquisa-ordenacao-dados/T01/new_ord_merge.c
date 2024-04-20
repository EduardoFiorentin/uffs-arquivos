#include "stdio.h"
#include "stdlib.h"
#include "linked_list.c"
#include "util.c"


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

void mergeSortAux(Tlist* A, int inicio, int fim) {
    if (inicio < fim) {
        int meio;
        meio = (int)(inicio + fim)/2;

        mergeSortAux(A, inicio, meio);
        mergeSortAux(A, meio + 1, fim);
        merge(A, inicio, meio, fim); 
    }
}

void mergeSort(Tlist* list, int listSize) {
    // int* vector = listToVector(list, listSize);
    Tlist* vector = listToStructVector(list, listSize);
    printf("\nValores do vetor: "); 
    for (int i = 0 ; i < listSize+1; i++) printf("%d ", vector[i].value);

    mergeSortAux(vector, 0, listSize);


    // sortedVectorToList(list, vector, listSize); 
    printf("\nTransformando vetor em lista...\n");
    list = structVectorToList(list, vector, listSize); 
    // free(vector); 
}

int main() {

    Tlist* linked_list = NULL; 

    printf("Inicio: ");
    printTList(linked_list); 

    int vector[] = {29, 8, 41, 11, 20 }; 
    int listSize = sizeof(vector)/sizeof(int);
    linked_list = vectorToNewList(linked_list, vector, listSize); 

    printf("\nAntes da ordenacao: ");
    printTList(linked_list); 
    
    mergeSort(linked_list, listSize-1);

    printf("\nDepois da ordenacao: ");
    printTList(linked_list); 

    freeList(linked_list);

    return 0; 
}