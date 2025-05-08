#ifndef FILES

#include <stdio.h>
#include "files.h"
#include <string.h>
#include <stdlib.h>
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

    if (feof(file)) {
        num.final = -1;
        return num;
    }

    while (!feof(file)) {
        c = getc(file);

        if (c != ';' && c != ' ') {
            str_num[pos] = c;
            pos++; 
        } 
        if (c == ';' || c == ' ') {
            str_num[pos] = '\0';
            num.value = atoi(str_num);
            if (c == ' ') num.final = 1;
            return num;
        }
    }
    num.final = 1;
    return num;
}


int is_file_empty(const char *filename) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fclose(file);

    if (file_size == 0) {
        return 1;
    } else {
        return 0;
    }
}

void create_new_aux_files( char* path, char* base_name, int num_files, FILE** files) {

     

    for (int i = 0; i < num_files; i++) {
        // Gera a string "aux_x" -> x: 0 a num_files - 1
        char str_num[20], base_name_local[20]; 
        sprintf(str_num, "%d", i);
        strcpy(base_name_local, path);
        strcat(base_name_local, base_name);
        strcat(base_name_local, str_num);
        strcat(base_name_local, ".txt");
        
        // gerar arquivos auxiliares
        printf("%s\n", base_name_local); 
        FILE* aux_file = fopen(base_name_local, "w+"); 
        files[i] = aux_file; 
    }

}