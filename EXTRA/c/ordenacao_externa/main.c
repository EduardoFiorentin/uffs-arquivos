#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    int i = 0, current_set_file = 0;

    if (is_file_empty(ENTRY_FILE_NAME)) {
        printf("Arquivo de leitura vazio.\n");  
    }


    // Cria dois vetores com arquivos para merge

    FILE** aux_files = malloc(sizeof(FILE*) * NUM_FILES);
    FILE** aux_files_set_1 = malloc(sizeof(FILE*) * M);
    FILE** aux_files_set_2 = malloc(sizeof(FILE*) * M);

    create_aux_files("data/", "aux_", NUM_FILES, aux_files); 

    for (int i = 0; i < NUM_FILES; i++) {
        if (i < NUM_FILES/2) {
            printf("a");
            aux_files_set_1[i] = aux_files[i];
        }
        else {
            printf("b");
            aux_files_set_2[i - (NUM_FILES/2)] = aux_files[i];
        }
    }

    // leitura arquivo inicial
    while ((num = read_next_int(file)).final != -1) {
        buffer[i++] = num.value; 
        if (num.final == 1 || num.final == -1 || i == M) {
            
            bubbleSort(buffer, i);
            
            if (ftell(aux_files_set_1[current_set_file]) != 0) {
                fputc(' ', aux_files_set_1[current_set_file]); 
            } 
            
            // Jogar dados para o arquivo auxiliar
            for (int j = 0; j < i; j++) {
                // printf("%d ", buffer[j]);
                if (j != i-1) fprintf(aux_files_set_1[current_set_file], "%d;", buffer[j]);
                else fprintf(aux_files_set_1[current_set_file], "%d", buffer[j]);
            }

            // incrementa o current_set_file circularmente, voltando para o zero ao chegar no limite
            current_set_file = (current_set_file + 1) % (NUM_FILES/2);
            // printf("\n");
            i = 0; 
        }
        
    }

    // merge dos sets de arquivos
    while (1) {
        
        if (merge_status_final(aux_files_set_1, M)) break;
        clear_files_of_set(aux_files_set_2, M);
        merge_sets(aux_files_set_1, aux_files_set_2, M); 

        if (merge_status_final(aux_files_set_2, M)) break;
        clear_files_of_set(aux_files_set_1, M);
        merge_sets(aux_files_set_2, aux_files_set_1, M); 
    }
    

    // Liberação de recursos
    fclose(file); 

    // for (int i = 0; i < NUM_FILES; i++) {
    //     fclose(aux_files[i]); 
    // }
    // for (int i = 0; i < (NUM_FILES/2); i++) {
    //     fclose(aux_files_set_1[i]); 
    // }
    // for (int i = 0; i < (NUM_FILES/2); i++) {
    //     fclose(aux_files_set_2[i]); 
    // }
    free(buffer);
    free(aux_files);    
    free(aux_files_set_1);
    free(aux_files_set_2);
    return 0;
}