#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "constants.h"
#include "dict_functions.h"

// inicia todos os valores da tabela de frequencia para evitar interferências do lixo de memória 
void begin_table_values(int table[]) {
    for (int i = 0; i < SIZE; i++) {
        table[i] = 0; 
    }
}

// faz a contagem dos caracteres do arquivo original de texto, incrementando 
// a posição relativa a cada caractere na tabela de frequência
void fill_freq_table( FILE* original_file, int freq_table[]) {
    int pos; 
    char c; 
    while (!feof(original_file)) {
        
        c = getc(original_file);
        pos = get_dict_position(c);

        if (pos != -1) freq_table[pos]++; 
    }
}
