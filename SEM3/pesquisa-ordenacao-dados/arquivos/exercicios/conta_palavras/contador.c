#include "stdio.h"
#include "stdlib.h"

int main() {

    FILE *arquivo = fopen("entrada.txt", "rt");


    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    // char palavras[10]; 
    char c;
    int ref; 
    int cont = 0; 

    while( !feof(arquivo) ) {
        c = getc(arquivo); 
        if (c != ' ') ref++; 
        if (c == ' ' && ref != 0) {
            ref = 0; 
            cont++; 
        }
        // printf("%c", c); 
    }; 
    printf("Numero palavras: %d\n", cont); 

    printf("Fechando...\n"); 
    fclose(arquivo); 

    return 0; 
}




// #include "stdio.h"

// int main() {

//     FILE* file = fopen("text.txt", "t"); 

//     if (file == NULL) {
//         printf("\nNão abriu o arquivo!");
//         return 1; 
//     }

    

//     printf("Fechando..."); 
//     fclose(file); 

//     return 0; 
// }