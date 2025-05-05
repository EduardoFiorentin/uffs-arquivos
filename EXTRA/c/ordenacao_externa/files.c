#ifndef FILES

#include <stdio.h>
#include "files.h"
#endif 

// Faz a leitura do proximo inteiro que aparece no arquivo
// .final = 0 - mais valores à frente 
// .final = 1 - final de bloco
// .final = -1 - final de arquivo
struct int_read read_next_int(FILE* file) {
    char c;
    char str_num[MAX_NUMS_LENGTH];
    int pos = 0;
    struct int_read num; 
    num.final = 0;

    while (!feof(file)) {
        c = getc(file);

        if (c != ';' && c != ' ') {
            str_num[pos] = c;
            pos++; 
        } 
        if (c == ';' || c == ' ' || feof(file)) {
            str_num[pos] = '\0';
            num.value = atoi(str_num);
            if (c == ' ') num.final = 1;
            return num;
        }
    }
    num.final = -1;
    return num; 
}
