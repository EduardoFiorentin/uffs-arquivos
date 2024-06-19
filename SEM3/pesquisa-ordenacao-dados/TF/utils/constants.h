#pragma once

// tamanho do dicionario de caracteres - numero de caracteres distintos 
#define SIZE 27

// nomes dos arquivos 
#define ORIGINAL_FILE "amostra.txt"
#define ENCODED_FILE "codificado.txt"
#define DECODED_FILE "decodificado.txt"

// lista de todos os caracteres possíveis na codificação
const char DICT_CHARS[] = {' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

// tipo utilizado para a árvore de huffman e para a lista encadeada
typedef struct node {
    char character; 
    int frequency; 
    struct node *left, *right, *next; 
} Node; 

// tipo que define uma lista encadeada
typedef struct list 
{
    Node* begin; 
    int size; 
} List;
