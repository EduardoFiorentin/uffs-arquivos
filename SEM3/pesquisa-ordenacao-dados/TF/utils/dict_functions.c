#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "constants.h"

// retorna a posição do caractere no vetor do dicionário
// retorna -1 caso o caractere passado não exista no vetor 
int get_dict_position(char c) {
    int i = 0; 
    while (i < SIZE) {
        if (DICT_CHARS[i] == c) return i; 
        i++;
    }
    return -1; 
}

// aloca memória para armazenamento do dicionario de codificação
//      size - tamanho da arvore 
char** dict_aloc(int size) {
    char** dict = (char**) malloc(sizeof(char*) * SIZE);

    // alocar ponteiros com espaço de memória vaziu
    for (int i = 0; i < SIZE; i++) dict[i] = (char*) calloc(size, sizeof(char));

    return dict; 
}



// gerar dicionario com os códigos de cada caractere
// percorre a arvore de huffman recursivamente, salvando os caminhos em uma variável interna.
// quando chega a um nó folha (que obrigatoriamente representa um dos caracteres), salva o caminho percorrido
// na posição correspondente ao caractere no dicionário 
void fill_dict(char **dict, Node *root, const char *path, int size) {

    // variáveis que guardam o caminho relativo para cada nodo 
    char left[SIZE], right[SIZE]; 

    // quando um nó folha é encontrado, o seu caminho na árvore é salvo no dicionário
    if (root->left == NULL && root->right == NULL) {

        // encontra a posição relativa ao caractere no dicionário e copia o caminho da raiz da arvore até 
        // o caractere para o dicionário
        strcpy(dict[get_dict_position(root->character)], path);
    } 

    // nos nodos intermediários, o caminho relativo é atualizado e a função é chamada recursivamente 
    // para continuar explorando a árvore 
    else {
        strcpy(left, path);
        strcpy(right, path); 

        strcat(left, "0"); 
        strcat(right, "1"); 

        fill_dict(dict, root->left, left, SIZE);
        fill_dict(dict, root->right, right, SIZE); 
    }
}