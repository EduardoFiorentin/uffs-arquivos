#include "stdio.h"
#include "stdlib.h"

int main() {

    FILE* file; 

    // abrir
    file = fopen("D:/github/uffs-arquivos/SEM3/pesquisa-ordenacao-dados/arquivos/paralelo/arquivo.txt", "r");

    if (file == NULL) {
        printf("Erro! Não abriu...");
        return 1; 
    }

    // manipular
    

    // fechar 
    fclose(file); 

    return 0; 
}