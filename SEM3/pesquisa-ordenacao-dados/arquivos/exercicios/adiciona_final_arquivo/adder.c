#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main() {

    
    char vector[100]; 
    int cont = 0;

    while (cont < 5) {
        FILE* file = fopen("text.txt", "a");

        if (file == NULL) {
            printf("Não foi possível abrir os arquivos.../n");
            exit(1);
        }


        printf("\nNova palavra: "); 
        scanf("%s", vector); 

        printf("\n%s ", vector); 

        // escrever no arquivo
        fputs(vector, file);
        fputs("\n", file);
        cont++; 
        fclose(file); 
    }


    printf("\nFechando..."); 

    return 0; 
}