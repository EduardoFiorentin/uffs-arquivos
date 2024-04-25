#include <stdio.h>
#include <stdlib.h>

int main() {

    FILE * fileIn = fopen("entrada.txt", "rt");
    FILE * fileOut = fopen("saida.txt", "wt");

    if (fileIn == NULL || fileOut == NULL) {
        printf("Não foi possível abrir os arquivos.../n");
        exit(1); 
    }

    char c; 

    while (!feof(fileIn)) {
        c = fgetc(fileIn); 
        if (c != EOF) fputc(c, fileOut); 
    }

    printf("Fechando...\n");
    fclose(fileIn);
    fclose(fileOut);
    return 0; 
}