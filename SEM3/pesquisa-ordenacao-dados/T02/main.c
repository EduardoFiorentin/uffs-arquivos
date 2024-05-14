#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linked_list.c>


#define SIZE_TEST 10
#define SIZE_LINE 35
#define SIZE_HASH 23

int hash(int num, int size_hash) {
    return size_hash % num; 
}

int main() {
    // ler numeros do arquivo de texto - casos_de_teste.txt

    FILE* file = fopen("casos_de_teste.txt", "r"); 
    int nums[SIZE_TEST]; 
    char line[SIZE_LINE];

    if (file == NULL) {
        printf("Erro na abertura do arquivo!");
        return 1; 
    }

    // definir todas as casas do array como -1
    for (int i = 0; i < SIZE_TEST; i++) {
        nums[i] = -1; 
    }

    fgets(line, SIZE_LINE, file);
    fclose(file);


    printf_s(line); 
    char *num = strtok(line, ";");
    int count = 0; 

    while (num != NULL) {
        nums[count] = atoi(num); 
        count++; 

        num = strtok(NULL, ";"); 
    }

    // criar hash table 
    Tlist* hash_table[SIZE_HASH]; 

    for (int i = 0; i < SIZE_HASH; i++) {
        hash_table[i] = NULL; 
    }


    // printar tabela hash completa 
        printf("Tabela hash:");
    for (int i = 0; i < SIZE_HASH; i++) {
        print("\tLinha %d", i); 
        printTList(hash_table[i]);
    }


    printf("\n");
    for (int i = 0; i < SIZE_TEST; i++) {
        printf("%d ", nums[i]); 
    }

    return 0; 
}




















// armazenar na tebela hash 
    // mod 23



    