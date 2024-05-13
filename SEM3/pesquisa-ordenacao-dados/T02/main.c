#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_TEST 10
#define SIZE_LINE 35

int main() {
    // ler numeros do arquivo de texto - casos_de_teste.txt

    FILE* file = fopen("casos_de_teste.txt", "r"); 
    int nums[SIZE_TEST]; 
    char line[SIZE_LINE];

    if (file == NULL) {
        printf("Erro na abertura do arquivo!");
        return 1; 
    }

    // definir todas as casas do array como -1
    for (int i = 0; i < SIZE_TEST; i++) {
        nums[i] = -1; 
    }

    fgets(line, SIZE_LINE, file);
    fclose(file);


    printf_s(line); 
    char *num = strtok(line, ";");
    int count = 0; 

    while (num != NULL) {
        nums[count] = atoi(num); 
        count++; 

        num = strtok(NULL, ";"); 
    }


    // for (int i = 0; i < SIZE_TEST; i++) {
    //     fgets(line, SIZE_LINE, file);
    // }

    printf("\n");
    for (int i = 0; i < SIZE_TEST; i++) {
        printf("%d ", nums[i]); 
    }

    return 0; 
}




















// armazenar na tebela hash 
    // mod 23



    