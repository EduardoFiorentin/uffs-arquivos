#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "constants.h"

// retorna a posição do caractere no vetor
int get_dict_position(const char dict_chars[], char chr) {
    int i = 0; 
    while (dict_chars[i] != chr) i++; 
    return i; 
}