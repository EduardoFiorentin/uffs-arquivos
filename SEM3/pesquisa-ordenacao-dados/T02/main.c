// AO MODIFICAR O ARQUIVO DE ENTRADA 
// atualizar o valor das constantes SIZE_TEST e SIZE_LINE
    // SIZE_TEST - quantos números estão no arquivo  de entrada
    // SIZE_LINE - quantos caracteres tem o arquivo de entrada + 1 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lists.c" 

#define SIZE_HASH 23                        // tamanho da tabela 
#define FILE_NAME "casos_de_teste.txt"      // nome do arquivo de entrada 


int hash(int num, int size_hash) {
    return num % size_hash; 
}

void loadData(Tlist** hash_table) {
    // ler numeros do arquivo de texto - casos_de_teste.txt
    FILE* file = fopen(FILE_NAME, "r");

    if (file == NULL) {
        printf("Erro na abertura do arquivo!\n");
        exit(1); 
    }

    // encontrar numero de caracteres e números 
    char c;
    char str_num[10];

    int pos = 0; 
    int num, hash_pos; 

    while(!feof(file)) {
        c = getc(file);
        if (c != ';') {
            str_num[pos] = c;
            pos++; 
        } 
        if (c == ';' || feof(file)) {
            str_num[pos] = '\0';
            pos = 0;

            num = atoi(str_num); 
            hash_pos = hash(num, SIZE_HASH);
            hash_table[hash_pos] = insertNode(hash_table[hash_pos], num);
        }
    };

    fclose(file);
}

int main() {
    // criar hash table 
    Tlist* hash_table[SIZE_HASH]; 

    for (int i = 0; i < SIZE_HASH; i++) {
        hash_table[i] = NULL; 
    }


    // inserir elementos na tabela
    loadData(hash_table); 


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




    