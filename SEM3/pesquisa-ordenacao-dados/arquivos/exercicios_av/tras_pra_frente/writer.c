#include <stdio.h>
#include <stdlib.h>

int main() {

    FILE* input_file = fopen("input.txt", "r");
    FILE* output_file = fopen("output.txt", "w+"); 

    if (input_file == NULL || output_file == NULL) {
        printf("Erro na abertura dos arquivos... \n");
        exit(1); 
    }

    // mover cursor para o final do arquivo
    fseek(input_file, 0, SEEK_END); 

    char ref, prev; 
    long position = ftell(input_file); 

    while (position) {
        fseek(input_file, --position, SEEK_SET);
        ref = fgetc(input_file);
        if (ref != '\n' || prev != '\n') {
            putc(ref, output_file); 
        }
        prev = ref;
    }

    fclose(input_file);
    fclose(output_file); 

    return 0;
}