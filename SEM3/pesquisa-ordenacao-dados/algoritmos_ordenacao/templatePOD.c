/**
 * @file nome_do_arquivo.c
 * @author Nome_do_Aluno
 * @version 0.2
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023
 *
 *
 * @brief Arquivo template para trabalho de Pesquisa e Ordenação.
 *
 *      Cada estudante deve implementar as funções conforme as assinaturas
 * abaixo e realizar as impressões dos vetores após a ordenação. Após, o(a)
 * estudante deve implementar o trecho de código para impressão dos vetores
 * ordenados dentro da função `main` conforme o exemplo do Bubble Sort abaixo.
 *
 * Atenção: Antes de entregar, conferir se dos dados acima da documentação estão
 * preenchidos corretamente.
 *
 */
#include <stdio.h>
#include <stdlib.h>

void troca (int *A, int i, int j) {
    int ref = A[i];
    A[i] = A[j];
    A[j] = ref;
}

void copia(int *A, int *v, int size) {
    for (int i = 0; i < size; i++) {
            v[i] = A[i];
    }
}

void bubbleSort(int *A, int size) {
    int i = size - 1;
    int j = 0;  
    int mudou, ref; 
    while (i >= 1) {
        mudou = 0; 
        j = 0; 
        while(j <= i-1) {
            if (A[j]>A[j+1]) {
                mudou = 1;
                ref = A[j];
                A[j] = A[j+1];
                A[j+1] = ref;
            }
            j++;
        }
        if (!mudou) break;
        i--;
    }
}

// trocar para o que usa vetor cópia
void selectionSort(int *A, int size) {
    int menor, ref;
    for (int i = 0; i <= size-2; i++) {
        menor = i;
        for (int j = i+1; j <= size-1; j++) {
            if (A[menor] > A[j]) menor = j; 
        }
        ref = A[i];
        A[i] = A[menor];
        A[menor] = ref;
    }
}


// selection sort estável 
// void selectionSort(int *A, int size) {
//     int menor, ref;
//     int auxVec[TAMANHO]; 

//     for (int i = 0 ; i < size-1 ; i++) {
  
        

//     }
// }


void insertionSort(int *A, int size) {
    int i, j, p; 
    for (i = 1; i < size; i++) {
        p = A[i];

        for(j = i; j >= 1 && p < A[j-1]; j--) {
            A[j] = A[j-1]; 
        }

        A[j] = p;
    }
}

// merge sort
void merge(int *A, int inicio, int meio, int fim) {
    int tamanho = fim-inicio+1;
    int* auxiliar = (int*)malloc(sizeof(int) * tamanho);
    
    // for (int n = 0; n < tamanho; n++) auxiliar[n] = -10; 

    int i = inicio;
    int j = meio + 1;
    int k = 0; 

    while (i <= meio && j <= fim) {
        if (A[i] <= A[j]) {
            auxiliar[k] = A[i];
            i++;
        } 
        else {
            auxiliar[k] = A[j];
            j++;
        }
        k++;
    }
    while (i <= meio) {
        auxiliar[k] = A[i];
        k++;
        i++;
    }
    while (j <= fim) {
        auxiliar[k] = A[j];
        k++;
        j++;
    }

    for (k = inicio; k <= fim; k++) {
        A[k] = auxiliar[k-inicio]; 
    }
    
    free(auxiliar);
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
void mergeSort(int *A, int size) {
    mergeSortAux(A, 0, size);
}


// quick sort

int particiona(int* A, int inicio, int fim) {
    int posPivo = fim;
    int k = inicio; 
    
    for (int i = inicio ; i < fim; i++) {
        if (A[i] <= A[posPivo]) {
            troca(A, i, k);
            k++; 
        }
    }

    if (A[k] > A[posPivo]) {
        troca(A, k, posPivo); 
    }
    return posPivo;
}

void quickS(int *A, int inicio, int fim) {
    if (inicio < fim) {
        int posPivo = particiona(A, inicio, fim); 
        quickS(A, inicio, posPivo-1);
        quickS(A, posPivo+1, fim);
    }
}

void quickSort(int *A, int size) {
    quickS(A, 0, size-1); 
};




// heap sort
void criaHeap(int* A, int i, int n) {
    int maior = i;
    int left = 2 * i + 1; 
    int right = 2 * i + 2;

    if (left < n && A[left] > A[i]) {
        maior = right;
    }

    if (right < n && A[right] > A[maior]) {
        maior = right;
    }

    if (maior != i ) {
        troca(A, i, maior); 
        criaHeap(A, maior, n);
    }
}

void heapSort(int *A, int size) {
    int k; 
    for (k = size/2-1; k >= 0; k--) {
        criaHeap(A, k, size);
    }

    for (k = size-1; k >= 1; k--) {
        criaHeap(A, 0, k);
    }
}


void countingSort(int *A, int size) {
    // printf("chegou aqui"); 
    int k = -1; 
    // encontra o maior
    for (int i = 0; i < size; i++) if (A[i] > k) k = A[i];

    // inicia vetor count 
    int* count;
    count = (int*) malloc((k * sizeof(int)) + 1);
    for (int i = 0; i <= k; i++) count[i] = 0; 

    // inicia vetor aux 
    int* aux;
    aux = (int*) malloc(size * sizeof(int)); 

    // incrementar contador 
    for (int i = 0; i < size; i++) count[A[i]]++; 

    // faz soma acumulada 
    for (int i = 1; i <= k; i++) count[i] += count[i-1]; 

    // inserir valores ordenados em aux 
    for (int i = size-1; i >= 0; i--) {
        count[A[i]] = count[A[i]] - 1; 
        aux[count[A[i]]] = A[i]; 
    }

    copia(aux, A, size); 

    free(count); 
    free(aux); 

}


// void radixSort(int *A, int size);


int main(){

    int vetor[] = {1, 2, 1, 2, 5, 2};
    int tamanhoVetor = (int)sizeof(vetor)/sizeof(int);

    printf("\nVetor original: ");
    for (int i = 0 ; i < tamanhoVetor ; i++)
        printf("%d ", vetor[i]);

    printf("\nVetor tamanho = %d\n", tamanhoVetor);

    // bubble sort
    // int bubbleVec[TAMANHO];
    int* bubbleVec;
    bubbleVec = (int*) malloc(tamanhoVetor * sizeof(int));
    copia(vetor, bubbleVec, tamanhoVetor);

    bubbleSort(bubbleVec, tamanhoVetor);

    printf("\nBubble sort: ");
    for (int i = 0 ; i < tamanhoVetor ; i++)
        printf("%d ", bubbleVec[i]);
    printf("\n");
    free(bubbleVec);

    // selection sort

    // int selectionVec[TAMANHO];
    int* selectionVec;
    selectionVec = (int*) malloc(tamanhoVetor * sizeof(int));
    copia(vetor, selectionVec, tamanhoVetor);

    printf("\nVetor original selection: ");
    for (int i = 0 ; i < selectionVec[i] ; i++)
        printf("%d ", vetor[i]);

    selectionSort(selectionVec, tamanhoVetor);

    printf("\nSelection sort: ");
    for (int i = 0 ; i < tamanhoVetor ; i++)
        printf("%d ", selectionVec[i]);
    printf("\n");

    free(selectionVec);


    // insertion sort
    // int insertionVec[TAMANHO];
    int* insertionVec;
    insertionVec = (int*) malloc(tamanhoVetor * sizeof(int));
    copia(vetor, insertionVec, tamanhoVetor);

    printf("\nInsertion sort before: ");
    for (int i = 0 ; i < tamanhoVetor ; i++)
        printf("%d ", insertionVec[i]);

    insertionSort(insertionVec, tamanhoVetor);

    printf("\nInsertion sort after: ");
    for (int i = 0 ; i < tamanhoVetor ; i++)
        printf("%d ", insertionVec[i]);
    printf("\n");printf("\n");
    free(insertionVec);



    // merge sort
    int* mergeVec;
    mergeVec = (int*) malloc(tamanhoVetor * sizeof(int));
    // int mergeVec[TAMANHO]; 
    copia(vetor, mergeVec, tamanhoVetor);
    printf("\nMerge sort before: ");
    for (int i = 0 ; i < tamanhoVetor ; i++)
        printf("%d ", mergeVec[i]);

    mergeSort(mergeVec, tamanhoVetor);

    printf("\nMerge sort after: ");
    for (int i = 0 ; i < tamanhoVetor ; i++)
        printf("%d ", mergeVec[i]);
    printf("\n");printf("\n");
    free(mergeVec);

    // quick sort
    // int quickVec[TAMANHO];
    int* quickVec;
    quickVec = (int*) malloc(tamanhoVetor * sizeof(int));
    copia(vetor, quickVec, tamanhoVetor);

    printf("Quick sort before: ");
    for (int i = 0 ; i < tamanhoVetor ; i++)
        printf("%d ", quickVec[i]);

    quickSort(quickVec, tamanhoVetor);

    printf("\nQuick sort after: ");
    for (int i = 0 ; i < tamanhoVetor ; i++)
        printf("%d ", quickVec[i]);
    printf("\n");printf("\n");

    free(quickVec);

    // heap sort
    // int heapVec[TAMANHO];
    int* heapVec;
    heapVec = (int*) malloc(tamanhoVetor * sizeof(int));
    copia(vetor, heapVec, tamanhoVetor);

    printf("Heap sort before: ");
    for (int i = 0 ; i < tamanhoVetor ; i++)
        printf("%d ", heapVec[i]);

    heapSort(heapVec, tamanhoVetor);

    printf("\nHeap sort after: ");
    for (int i = 0 ; i < tamanhoVetor ; i++)
        printf("%d ", heapVec[i]);
    printf("\n");printf("\n");
    // printf("Chegou"); 

    free(heapVec);

    // counting sort
    // printf("Tamanho vet: %d", tamanhoVetor);
    int* countingVec;
    countingVec = (int*)malloc(tamanhoVetor * sizeof(int));
    copia(vetor, countingVec, tamanhoVetor);

    printf("Counting sort before: ");
    for (int i = 0 ; i < tamanhoVetor ; i++)
        printf("%d ", countingVec[i]);

    countingSort(countingVec, tamanhoVetor);

    printf("\nCounting sort after: ");
    for (int i = 0 ; i < tamanhoVetor ; i++)
        printf("%d ", countingVec[i]);
    printf("\n");printf("\n");

    free(countingVec); 

    // radix sort

    return 0;
}



