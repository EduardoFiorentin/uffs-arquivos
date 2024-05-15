// AO MODIFICAR O ARQUIVO DE ENTRADA 
// atualizar o valor das constantes SIZE_TEST e SIZE_LINE
    // SIZE_TEST - quantos números estão no arquivo  de entrada
    // SIZE_LINE - quantos caracteres tem o arquivo de entrada + 1 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lists.c" 

#define SIZE_TEST 45    // quantidade de números presentes no arquivo de entrada  
#define SIZE_LINE 125    // numero de caracteres da 1ª linha do arquivo de entada + 1 
#define SIZE_HASH 23    // tamanho da tabela 


int hash(int num, int size_hash) {
    return num % size_hash; 
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


    char *token = strtok(line, ";");
    int count = 0; 

    while (token != NULL) {
        nums[count] = atoi(token); 
        count++; 

        token = strtok(NULL, ";"); 
    }

    // criar hash table 
    Tlist* hash_table[SIZE_HASH]; 

    for (int i = 0; i < SIZE_HASH; i++) {
        hash_table[i] = NULL; 
    }


    // inserir elementos na tabela
    int pos; 
    for (int i = 0 ; i < SIZE_TEST; i++) {
        pos = hash(nums[i], SIZE_HASH);
        hash_table[pos] = insertNode(hash_table[pos], nums[i]);
    }


    // printar tabela hash completa 
        printf("Tabela hash:");
    for (int i = 0; i < SIZE_HASH; i++) {
        printf("\n   L%02d:", i); 
        printTList(hash_table[i]);
    }
    printf("\n");

    for (int i = 0; i < SIZE_HASH; i++) {
        freeList(hash_table[i]);
    }

    return 0; 
}




    