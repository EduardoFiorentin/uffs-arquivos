#include <stdlib.h>
#include <stdio.h>
#include "dict_functions.h"
#include "constants.h"

// lê caractere por caractere de um arquivo e codifica-os com base nos códigos do dicionário, salvando-os 
// em um segundo arquivo 
void encode_file_text(FILE *original_file, FILE *encoded_file, char** dict) {
    char c; 
    int pos; 
    fseek(original_file, 0, SEEK_SET); // garante que a leitura inicie no inicio do arquivo 

    while(!feof(original_file)) {
        c = getc(original_file);

        pos = get_dict_position(c); 
        if (pos != -1) fputs(dict[pos], encoded_file); 
    }

}

// lê um arquivo codificado e decodifica usando a árvore de huffman, salvando os caracteres encontrados 
// em um novo arquivo 
void decode_file_text(FILE *encoded_file, FILE *decoded_file, Node *huffman_tree) {
    Node *aux = huffman_tree; 
    char c; 

    fseek(encoded_file, 0, SEEK_SET); // garante que a leitura inicie no inicio do arquivo 

    while (!feof(encoded_file)) {
        c = getc(encoded_file); 

        // percorre a arvore até encontrar um nó folha (caractere)
        if (c == '0') {
            aux = aux->left;
        }
        else if (c == '1') {
            aux = aux->right; 
        }
        else {
            break;
        }

        // quando encontrar um nó folha, que representa um caractere.
        if (aux->left == NULL && aux->right == NULL) {
            fputc(aux->character, decoded_file); 
            aux = huffman_tree; 
        }
    }

}