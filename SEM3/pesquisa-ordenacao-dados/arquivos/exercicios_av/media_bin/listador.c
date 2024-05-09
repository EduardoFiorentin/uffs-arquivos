#include <stdio.h>
#include <stdlib.h>

#define TAMANHO 10

int main() {

  FILE* file = fopen("file.dat", "rb");

  if (file == NULL) {
    printf("Erro!");
    exit(1); 
  }

  int reg[TAMANHO]; 
  fread(reg, sizeof(int), TAMANHO, file);

  int min, max, sum; 

  min = reg[0];
  max = reg[0]; 
  sum = 0; 

  for (int i = 0; i < TAMANHO; i++) {
    if (min > reg[i]) min = reg[i];
    if (max < reg[i]) max = reg[i]; 
    sum += reg[i]; 
  }

  printf("Minimo: %d\n", min); 
  printf("Maximo: %d\n", max); 
  printf("Media: %.2f\n", (double) sum/TAMANHO); 

  fclose(file); 

  return 0; 
}
