#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "files.h"
#include "sort.h"


int read_M() {
    int value;
    printf("Numero de elementos carregados por vez: ");
    scanf("%d", &value);
    return value; 
}

// Abre o arquivo dados.txt com os dados a serem ordenados
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
    
    if (M < 2) {
        printf("M Precisa ser pelo menos 2\n");
        exit(1);
    }

    NUM_FILES = M * 2; 

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
    struct aux_file* aux_files = malloc(sizeof(struct aux_file) * NUM_FILES);
    struct aux_file* aux_files_set_1 = malloc(sizeof(struct aux_file) * M);
    struct aux_file* aux_files_set_2 = malloc(sizeof(struct aux_file) * M);

    // cria arquivos auxiliares para o merge
    create_aux_files("data/", "aux_", NUM_FILES, aux_files); 

    for (int i = 0; i < NUM_FILES; i++) {
        if (i < NUM_FILES/2) {
            aux_files_set_1[i].file = aux_files[i].file;
            strcpy(aux_files_set_1[i].name, aux_files[i].name);
            
        }
        else {
            aux_files_set_2[i - (NUM_FILES/2)].file = aux_files[i].file;
            strcpy(aux_files_set_2[i - (NUM_FILES/2)].name, aux_files[i].name);
        }
    }


    // faz a leitura inicial do dados.txt, separando em blocos de M inteiros no
    // primeiro set de arquivos auxiliares 
    while ((num = read_next_int(file)).final != -1) {
        buffer[i++] = num.value; 
        if (num.final == 1 || num.final == -1 || i == M) {
            
            bubbleSort(buffer, i);
            
            if (ftell(aux_files_set_1[current_set_file].file) != 0) {
                fputc(' ', aux_files_set_1[current_set_file].file); 
            } 
            
            // Jogar dados para o arquivo auxiliar
            for (int j = 0; j < i; j++) {
                if (j != i-1) fprintf(aux_files_set_1[current_set_file].file, "%d;", buffer[j]);
                else fprintf(aux_files_set_1[current_set_file].file, "%d", buffer[j]);
            }

            // incrementa o current_set_file circularmente, voltando para o zero ao chegar no limite
            current_set_file = (current_set_file + 1) % (NUM_FILES/2);
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

    for (int i = 0; i < NUM_FILES; i++) {
        fclose(aux_files[i].file); 
    }
    free(buffer);
    free(aux_files);    
    free(aux_files_set_1);
    free(aux_files_set_2);
    return 0;
}