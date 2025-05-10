#ifndef FILES_H
#define FILES_H

#include <stdio.h>

#define ENTRY_FILE_NAME     "data/dados.txt"
#define MAX_NUMS_LENGTH     10
#define MAX_LEN_NAME_AUX    30
#define INFINITY            100000000

struct int_read {
    int value;          // valor lido do arquivo
    int final;          // final de bloco encontrado  
};

struct merge_aux {
    int value;          // Valor lido do arquivo 
    FILE* file;         // Arquivo sendo lido
    int has_next_read;  // Ainda há valores no bloco para ler
};

struct aux_file {
    FILE* file;                       // Arquivo auxiliar
    char name[MAX_LEN_NAME_AUX];      // Nome do arquivo auxiliar
};

struct int_read     read_next_int(FILE* file);
int                 is_file_empty(const char *filename); 
void                create_aux_files( char* path,  char* base_name, int num_files, struct aux_file* files);
int                 merge_status_final(struct aux_file* file_set, int M); 
void                merge_sets(struct aux_file* origin, struct aux_file* target, int M);
long                get_file_size(FILE *file);
void                clear_files_of_set(struct aux_file* file_set, int M);
void                clear_file(FILE *file);

#endif // FILES_H