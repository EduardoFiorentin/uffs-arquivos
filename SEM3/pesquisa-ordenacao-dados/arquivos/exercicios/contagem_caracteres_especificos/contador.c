#include <stdio.h>
#include <stdlib.h>

int main() {

    FILE *file = fopen("text.txt", "r"); 

    if (file == NULL) {
        printf("Erro! Arquivo nao encontrado!\n");
        system("pause"); 
        exit(1);
    }

    char ref, esc; 
    int cont = 0; 

    system("cls");
    printf("Escolha o caractere para ser procurado: ");
    scanf("%c", &esc); 

    while (!feof(file)) {
        ref = fgetc(file); 
        if (ref == esc) cont++;
    }

    printf("Foram encontrados %d caracteres do tipo '%c'.\n", cont, esc);

    fclose(file); 
    system("pause"); 

    return 0; 
}