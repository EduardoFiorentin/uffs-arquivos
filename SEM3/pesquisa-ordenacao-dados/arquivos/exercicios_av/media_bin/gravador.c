// Escreve N valores reais aleatórios em um arquivo, em formato binário
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
#define ARQUIVO "numeros.dat"
#define NUMVAL 10

int gera_aleatorio() {
    return (rand() % 100) + 1; // gera um número entre 1 e 100
}
 
int main () {
  srand(clock()); // usa o tempo atual como semente para a função rand()
  
  FILE* arq ;
  int i, ret ;
  int value[NUMVAL] ;
 
  // abre o arquivo em modo "append"
  arq = fopen (ARQUIVO, "w+") ;
  if (!arq)
  {
    perror ("Erro ao abrir arquivo") ;
    exit (1) ;
  }
 
 
  // gera NUMVAL valores aleatórios reais
  for (i = 0; i < NUMVAL; i++)
    value[i] = gera_aleatorio();
 
  // escreve os valores gerados no final do arquivo
  ret = fwrite (value, sizeof (int), NUMVAL, arq) ;
  if (ret)
    printf ("Gravou %d valores com sucesso!\n", ret) ;
  else
    printf ("Erro ao gravar...\n") ;
 
  // fecha o arquivo
  fclose (arq) ;
  return (0) ;
}