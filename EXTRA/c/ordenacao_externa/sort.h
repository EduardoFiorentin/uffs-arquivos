#ifndef SORT_H
#define SORT_H

#include "files.h"

void        swap(int *a, int *b);
void        bubbleSort(int arr[], int n);
void        swap_merge_aux(struct merge_aux *a, struct merge_aux *b);
void        bubbleSort_merge_aux(struct merge_aux arr[], int n);

#endif // SORT_H