#ifndef FILES
    #include <stdio.h>
#endif


#define ENTRY_FILE_NAME "dados.txt"
#define MAX_NUMS_LENGTH 10

struct int_read {
    int value;     // valor lido do arquivo
    int final;     // final de bloco encontrado  
};

struct int_read  read_next_int(FILE* file);