#ifndef FILES_H
#define FILES_H

#include <stdio.h>

#define ENTRY_FILE_NAME     "data/dados.txt"
#define MAX_NUMS_LENGTH     10
#define INFINITY            100000000

struct int_read {
    int value;     // valor lido do arquivo
    int final;     // final de bloco encontrado  
};

struct merge_aux {
    int value;
    FILE* file; 
    int has_next_read; 
    char file_name[30]; 
};

struct int_read     read_next_int(FILE* file);
int                 is_file_empty(const char *filename); 
void                create_aux_files( char* path,  char* base_name, int num_files, FILE** files);
int                 merge_status_final(FILE** file_set, int M); 
void                merge_sets(FILE** origin, FILE** target, int M);
long                get_file_size(FILE *file);
void                clear_files_of_set(FILE** file_set, int M);
void                clear_file(FILE *file);

#endif // FILES_H