// Leitura e Impressão de Linhas Específicas: Escreva um programa que leia um
// arquivo de texto linha por linha e imprima apenas as linhas que começam com uma
// determinada letra ou palavra especificada pelo usuário.

#include <stdio.h>
#include <stdlib.h>

int main() {
    system("cls");

    FILE* file = fopen("text.txt", "r+");

    if (file == NULL) {
        printf("Erro!"); 
        exit(1); 
    }

    // ler o inicio da frase        
    char begin[100]; 
    char line[100]; 
    char ref = '0'; 
    int i, print; 

    // colatar inicio da linha 
    printf("Inicio da string: ");
    scanf("%s", begin); 
    printf("\nFrases que comecam com: '%s'\n", begin);

    while (!feof(file)) {
        fgets(line, 100, file); 
        i = 0;
        print = 1;

        // comparar com o inicio de cada linha
        while (1) {
            ref = begin[i];
            if (ref == '\0') break; 

            if (begin[i] != line[i]) {
                print = 0; 
                break;
            }; 
            i++; 
        }


        if (print) printf("%s", line);
    }

    // while (fgets(begin, sizeof(begin), file) != NULL) {
    //     printf("%s", begin); // Imprime a begin
    // }

        // ler a linha 

        // comparar com o begin

    // para todo o begin: compara com o inicio de cada linha
        // se diferente passa pra próxima 
        // se chegar no fim do inicio e não saiu: imprime a linha


    fclose(file);
    printf("\nFim!\n"); 

    return 0; 
}