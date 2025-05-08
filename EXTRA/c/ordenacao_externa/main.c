#include <stdio.h>
#include <stdlib.h>
#include "files.h"
#include "sort.h"


int read_M() {
    int value;
    printf("\nNumero de elementos carregados por vez: ");
    scanf("%d", &value);
    return value; 
}

FILE* open_main_file() {
    FILE* file = fopen(ENTRY_FILE_NAME, "r");

    if (file == NULL) {
        printf("Erro na abertura do arquivo!\n");
        exit(1); 
    }

    return file; 
}

int main(int argc, char *argv[]) {

    int M, *buffer, NUM_FILES; 
    FILE* file;

    // Leitura do valor de M
    // se passado como argumento, não faz a leitura do terminal
    if (argc > 1)
        M = atoi(argv[1]);
    else
        M = read_M(); 
    
    NUM_FILES = M * 2; 
    
    printf("Numero de M: %d\n", M);

    // abre o arquivo com os dados para ordenação
    file = open_main_file();

    // aloca memória para o buffer de carregamento dos dados 
    buffer = malloc(M * sizeof(int)); 

    struct int_read num;
    int i = 0;
    
    if (is_file_empty(ENTRY_FILE_NAME)) {
        printf("Arquivo de leitura vazio.\n");  
    }

    // leitura dos blocos de um arquivo ou arquivo de entrada
    while ((num = read_next_int(file)).final != -1) {
        buffer[i++] = num.value; 
        if (num.final == 1 || num.final == -1 || i == M) {
            bubbleSort(buffer, i);
            for (int j = 0; j < i; j++) {
                printf("%d ", buffer[j]);
            }
            printf("\n");
            i = 0; 
        }
        
    }

    FILE** files = malloc(sizeof(FILE*) * NUM_FILES);

    create_new_aux_files("data/", "aux_", NUM_FILES, files); 

    for (int i = 0; i < NUM_FILES; i++) {
        fprintf(files[i], "Teste de escrita arquivo"); 
    }

    fclose(file); 

    for (int i = 0; i < NUM_FILES; i++) {
        fclose(files[i]); 
    }

    free(buffer);
    free(files); 
    return 0;
}