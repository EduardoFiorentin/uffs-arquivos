#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO 10

int main() {

  FILE* file = fopen("grade.txt", "r");

  if (file == NULL) {
    printf("Erro!");
    exit(1); 
  }

    char stud[50]; 
    char greater_stud[50]; 
    double sum, grade, max_grade;

    max_grade = -1; 

    while (!feof(file)) {
        fscanf(file, "%s %lf", stud, &grade); 
        if (max_grade < grade) {
            max_grade = grade;
            strcpy(greater_stud, stud); 
        }; 

    }
  printf("Melhor: %s %.2lf\n", greater_stud, max_grade); 

  fclose(file); 

  return 0; 
}
