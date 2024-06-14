#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "utils/linkedList.c"
#include "utils/constants.h"
#include "utils/dict_functions.c"
#include "utils/huffmanTree.c"
#include "utils/frequency_table.c"

int main() {


// ler o texto
    char text[] = "abracadabra"; 

    // abertura dos arquivos necessários no sistema 
    FILE *original_file = fopen(ORIGINAL_FILE, "r"); 
    FILE *encoded_file = fopen(ENCODED_FILE, "w"); 

    if (original_file == NULL || encoded_file == NULL) {
        printf("Não foi possível abrir um dos arquivos necessários!"); 
        exit(1); 
    }


// gerar tabela de frequência 
// a tabela guarda o espaço no primeiro slot e o alfabeto minusculo na sequencia
    int freq_table[SIZE];

    begin_table_values(freq_table);
    fill_freq_table(text, freq_table, DICT_CHARS, DICT_POSITION); 
    print_table_freq(freq_table);




// gerar lista encadeada com nodos da arvore 

    List list; 
    begin_list(&list); 
    fill_list(&list, freq_table, DICT_CHARS);

    print_list(&list); 


    

// gerar arvore de huffman 

    Node* huffman_tree = assemble_huffman_tree(&list); 
    printf("Avore de huffman: \n"); 
    print_huffman_tree(huffman_tree, 0); 

// gerar dicionario de codificação

    int tree_h = tree_height(huffman_tree); // apenas para testar 
    char **dict = dict_aloc(SIZE);
    fill_dict(dict, huffman_tree, "", SIZE);
    print_dict(dict);

// liberar memória alocada para a lista encadeada


// codificar texto 


    // posicionar cursor no inicio do arquivo original 

    // ler caractere por caractere do arquivo original, escrevendo o código 
    // correspondente no codificado 
    char c; 
    fseek(original_file, 0, SEEK_SET);
    while(!feof(original_file)) {
        c = getc(original_file); 
        fputs(dict[get_dict_position(c)], encoded_file); 
    }

    fclose(original_file);
    fclose(encoded_file); 


// decodificar arquivo 


}


// OBS: Inteiros da tabela 

// 32 - ' '
// 97 - 'a'
// ...
// 122 - 'z'