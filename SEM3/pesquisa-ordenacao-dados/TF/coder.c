#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "utils/linkedList.c"
#include "utils/constants.h"
#include "utils/dict_functions.h"
#include "utils/huffmanTree.c"


void begin_table_values(int table[]) {
    for (int i = 0; i < SIZE; i++) {
        table[i] = 0; 
    }
}

// unsigned acess_freq_table(char chr) {
//     if (chr == ' ') return 0;
//     else {
//         int space = (int) ' '; 
//         int a = (int) 'a';
//         int z = (int) 'z';  
//         return 
//     }
// }

void fill_freq_table( char text[], int freq_table[], const char dict_chars[], const int dict_position[]) {
    // int i = 0; 
    // while (text[i] != '\0') {
    //     table[text[i]]++; 
    //     i++;
    // }

    int i = 0; 
    int j = 0; 
    while (text[i] != '\0') {
        j = 0;
        while ( j < SIZE ) {
            if (text[i] == dict_chars[j]) {
                freq_table[dict_position[j]]++; 
                break; 
            }
            j++; 
        }
        i++; 
    }

}

void print_table_freq(int table[]) {
    for (int i = 0; i < SIZE; i++) {
        printf("\t%d = %d\n", i, table[i], i); 
    }
}

int main() {


// ler o texto
    char text[] = "codificacao de huffman"; 


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


// liberar memória alocada para a lista encadeada


// codificar texto 


// gravar texto no arquivo codificado 


}


// OBS: Inteiros da tabela 

// 32 - ' '
// 97 - 'a'
// ...
// 122 - 'z'