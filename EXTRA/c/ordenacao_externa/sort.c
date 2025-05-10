#include "sort.h"

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Função para ordenar um array usando o Bubble Sort
void bubbleSort(int arr[], int n) {
    int i, j;
    int swapped;

    for (i = 0; i < n - 1; i++) {
        swapped = 0;
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                swapped = 1;
            }
        }
        if (swapped == 0) break;
    }
}


void swap_merge_aux(struct merge_aux *a, struct merge_aux *b) {
    struct merge_aux temp = *a;
    *a = *b;
    *b = temp;
}

// Função para ordenar um array usando o Bubble Sort
void bubbleSort_merge_aux(struct merge_aux arr[], int n) {
    int i, j;
    int swapped;

    for (i = 0; i < n - 1; i++) {
        swapped = 0;
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j].value > arr[j + 1].value) {
                swap_merge_aux(&arr[j], &arr[j + 1]);
                swapped = 1;
            }
        }
        if (swapped == 0) break;
    }
}
