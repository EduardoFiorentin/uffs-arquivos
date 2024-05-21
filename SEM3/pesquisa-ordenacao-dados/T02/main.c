#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lists.c" 

#define SIZE_HASH 23                        // tamanho da tabela 
#define FILE_NAME "casos_de_teste.txt"      // nome do arquivo de entrada 

// função que define a posição dos números na tabela hash
int hash(int num, int size_hash) {
    return num % size_hash; 
}

// carreaga os números do arquivo externo em uma tabela hash
void loadData(Tlist** hash_table) {

    // carregar dados do arquivo de texto - casos_de_teste.txt
    FILE* file = fopen(FILE_NAME, "r");

    if (file == NULL) {
        printf("Erro na abertura do arquivo!\n");
        exit(1); 
    }

    char c;
    char str_num[10];

    int pos = 0; 
    int num, hash_pos; 

    // percorre o arquivo de texto carregado digito a digito, salvando os digitos encontrados 
    // em uma string
    // quando um ; é encontrado ou a leitura chega ao final do arquivo, um \0 é adicionado para 
    // sinalizar o final da string e, então, a função atoi() converte a string em inteiro, e em 
    // seguida o número é adicionado à tabela. 
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

    // inicializar todos os campos da tabela como null
    for (int i = 0; i < SIZE_HASH; i++) {
        hash_table[i] = NULL; 
    }


    // inserir elementos do arquivo na tabela
    loadData(hash_table); 


    // imprimir tabela hash completa 
    printf("Tabela hash:");
    for (int i = 0; i < SIZE_HASH; i++) {
        printf("\n   L%02d:", i); 
        printTList(hash_table[i]);
    }
    printf("\n");

    // liberar memória alocada para os nodos da tabela
    for (int i = 0; i < SIZE_HASH; i++) {
        freeList(hash_table[i]);
    }

    return 0; 
}




    