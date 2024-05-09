#include <stdio.h>
#include <stdlib.h>

#define TAMANHO 10

int main() {

  FILE* file = fopen("file.dat", "wb+");

  if (file == NULL) {
    printf("Erro!");
    exit(1); 
  }

  int i[TAMANHO] = {10, 9, 3, 66, 5, 34, 102, 3, 7, 45}; 
  fwrite(i, sizeof(int), TAMANHO, file);

  fclose(file); 

  return 0; 
}
