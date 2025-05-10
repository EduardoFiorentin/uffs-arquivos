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

void create_aux_files( char* path, char* base_name, int num_files, FILE** files) {
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

// Verifica se apenas um dos arquivos do set tem valores
int merge_status_final(FILE** file_set, int M) {
    int count = 0;
    for (int i = 0; i < (M); i++) {
        if (get_file_size(file_set[i]) != 0) {
            count++;
        }
    }

    if (count == 1) return 1;
    return 0;
} 

void merge_sets(FILE** origin, FILE** target, int M) {

    struct merge_aux buffer[M];
    struct int_read num; 
    int final = 0, current_target = 0, first = 0;

    // inicia as variáveis necessárias e carrega os primeiros valores no buffer 
    for (int i = 0; i < M; i++) {
        buffer[i].file = origin[i];
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

    for (int i = 0; i < M; i++) {
        printf("\nInicio - %d %d %p", buffer[i].value, buffer[i].has_next_read, buffer[i].file);
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
                if (ftell(target[current_target]) != 0) {
                    fputc(' ', target[current_target]); 
                } 
                fprintf(target[current_target], "%d", buffer[0].value);
            } 
            else  {
                fprintf(target[current_target], ";%d", buffer[0].value); 
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

        printf("\n\nRecalculo\n\n");

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


    for (int i = 0; i < M; i++) {
        printf("\n%d %p", buffer[i].value, buffer[i].file);
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
void clear_files_of_set(FILE** file_set, int M) {
    for (int i = 0; i < (M); i++) {
        clear_file(file_set[i]);
    }
}

// Limpa o conteúdo de um arquivo
// Volta o cursor para o inicio
void clear_file(FILE *file) {
    fseek(file, 0, SEEK_SET);
    ftruncate(fileno(file), 0);
}