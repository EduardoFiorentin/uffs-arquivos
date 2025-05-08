#ifndef FILES
    #include <stdio.h>
#endif


#define ENTRY_FILE_NAME     "data/dados.txt"
#define MAX_NUMS_LENGTH     10

struct int_read {
    int value;     // valor lido do arquivo
    int final;     // final de bloco encontrado  
};

struct int_read     read_next_int(FILE* file);
int                 is_file_empty(const char *filename); 
void                create_new_aux_files( char* path,  char* base_name, int num_files, FILE** files);