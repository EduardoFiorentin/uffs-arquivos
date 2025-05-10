#ifndef FILES

#include <stdio.h>
#include "files.h"
#include <string.h>
#include <stdlib.h>
#include "sort.h"
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

    if (feof(file) || get_file_size(file) == 0) {
        num.final = -1;
        num.value = -1;
        return num;
    }

    while (!feof(file)) {
        c = getc(file);

        if (c != ';' && c != ' ') {
            str_num[pos] = c;
            pos++; 
        } 
        if (c == ';') {
            str_num[pos] = '\0';
            num.value = atoi(str_num);
            num.final = 0;
            return num;
        }
        if (c == ' ') {
            str_num[pos] = '\0';
            num.value = atoi(str_num);
            num.final = 1;
            return num;
        }
        
    }

    if (pos > 0) {
        str_num[pos] = '\0';
        num.value = atoi(str_num);
        num.final = 1;
        return num;
    }

    num.final = -1;
    num.value = -1;
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

void create_aux_files( char* path, char* base_name, int num_files, struct aux_file* files) {
    for (int i = 0; i < num_files; i++) {
        // Gera o nome do arquivo
        char str_num[MAX_LEN_NAME_AUX], base_name_local[MAX_LEN_NAME_AUX]; 
        sprintf(str_num, "%d", i);
        strcpy(base_name_local, path);
        strcat(base_name_local, base_name);
        strcat(base_name_local, str_num);
        strcat(base_name_local, ".txt");
        
        // gerar arquivo auxiliar
        struct aux_file aux_file;
        aux_file.file = fopen(base_name_local, "w+");
        strcpy(aux_file.name, base_name_local);

        files[i] = aux_file; 
    }

}

// Verifica se apenas um dos arquivos do set tem valores
int merge_status_final(struct aux_file* file_set, int M) {
    int count = 0;
    char name[MAX_LEN_NAME_AUX];
    for (int i = 0; i < (M); i++) {
        if (get_file_size(file_set[i].file) != 0) {
            count++;
            strcpy(name, file_set[i].name);
        }
    }

    if (count == 1) {
        printf("\nArquivo com resultado: %s\n", name);
        return 1;
    }
    return 0;
} 

void merge_sets(struct aux_file* origin, struct aux_file* target, int M) {

    struct merge_aux buffer[M];
    struct int_read num; 
    int final = 0, current_target = 0, first = 0;

    // inicia as variáveis necessárias e carrega os primeiros valores no buffer 
    for (int i = 0; i < M; i++) {
        buffer[i].file = origin[i].file;
        fseek(buffer[i].file, 0, SEEK_SET);
        num = read_next_int(buffer[i].file); 

        if (num.final == -1) {
            buffer[i].value = INFINITY; 
            buffer[i].has_next_read = 0;
        }
        else {
            buffer[i].value = num.value;
            if ( num.final == 1) {
                buffer[i].has_next_read = 0;
            } 
            else {
                buffer[i].has_next_read = 1;
            }
        }
    }

    while (1) {
        final = 1; 
        first = 1;
        while(1) {

            bubbleSort_merge_aux(buffer, M);
    
            if (buffer[0].value == INFINITY) break; 

            final = 0; 

            // escreve menor numero
            if (first) {
                if (ftell(target[current_target].file) != 0) {
                    fputc(' ', target[current_target].file); 
                } 
                fprintf(target[current_target].file, "%d", buffer[0].value);
            } 
            else  {
                fprintf(target[current_target].file, ";%d", buffer[0].value); 
            }
            first = 0;
            
            // lê o proximo numero do arquivo
            if (buffer[0].has_next_read) {
                num = read_next_int(buffer[0].file); 
                // buffer[0].value = (num.final != 0) ? num.value : INFINITY;

                if (num.final == -1) {
                    buffer[0].value = INFINITY; 
                    buffer[0].has_next_read = 0;
                }
                else {
                    buffer[0].value = num.value;
                    if ( num.final == 1) {
                        buffer[0].has_next_read = 0;
                    } 
                    else {
                        buffer[0].has_next_read = 1;
                    }
                }
            }
            else {
                buffer[0].value = INFINITY; 
            }
            
        }

        
        current_target = (current_target + 1) % M;
        if (final) break; 

        for (int i = 0; i < M; i++) {
            num = read_next_int(buffer[i].file);
            if (num.final == -1) {
                buffer[i].value = INFINITY; 
                buffer[i].has_next_read = 0;
            }
            else {
                buffer[i].value = num.value;
                if ( num.final == 1) {
                    buffer[i].has_next_read = 0;
                } 
                else {
                    buffer[i].has_next_read = 1;
                }
            }
        }
    }

} 


long get_file_size(FILE *file) {
    long originalPosition = ftell(file);

    fseek(file, 0, SEEK_END);

    long fileSize = ftell(file);

    fseek(file, originalPosition, SEEK_SET);

    return fileSize;
}

// limpa todos os arquivos do set
void clear_files_of_set(struct aux_file* file_set, int M) {
    for (int i = 0; i < (M); i++) {
        clear_file(file_set[i].file);
    }
}

// Limpa o conteúdo de um arquivo
// Volta o cursor para o inicio
void clear_file(FILE *file) {
    fseek(file, 0, SEEK_SET);
    ftruncate(fileno(file), 0);
}