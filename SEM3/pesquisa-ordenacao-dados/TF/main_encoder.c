#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "utils/linkedList.c"
#include "utils/constants.h"
#include "utils/dict_functions.c"
#include "utils/huffman_tree.c"
#include "utils/frequency_table.c"
#include "utils/text_transformer.c"

int main() {


// leitura de arquivos 

    // abertura dos arquivos necessários no sistema 
    FILE *original_file = fopen(ORIGINAL_FILE, "r"); 
    FILE *encoded_file = fopen(ENCODED_FILE, "w"); 
    FILE *decoded_file = fopen(DECODED_FILE, "w"); 

    if (original_file == NULL || encoded_file == NULL || decoded_file == NULL) {
        printf("Não foi possível abrir um dos arquivos necessários!"); 
        exit(1); 
    }


// gerar tabela de frequência 
// a tabela guarda o espaço no primeiro slot e o alfabeto minusculo na sequencia
    int freq_table[SIZE];

    begin_table_values(freq_table);
    fill_freq_table(original_file, freq_table); 
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

    // int tree_h = tree_height(huffman_tree); // apenas para testar 
    char **dict = dict_aloc(SIZE);
    fill_dict(dict, huffman_tree, "", SIZE);
    print_dict(dict);

// liberar memória alocada para a lista encadeada


// codificar texto 
    encode_file_text(original_file, encoded_file, dict); 
    fclose(encoded_file);
    fclose(original_file);



// decodificar arquivo 
    // abrir arquivo codificado novamente no modo leitura para acessar o conteúdo gravado 
    encoded_file = fopen(ENCODED_FILE, "r"); 
    decode_file_text(encoded_file, decoded_file, huffman_tree); 


// fechar arquivos 
    fclose(decoded_file); 
    fclose(encoded_file);
}
