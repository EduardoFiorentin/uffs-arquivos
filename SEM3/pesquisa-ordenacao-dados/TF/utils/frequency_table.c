#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "utils/constants.h"


void begin_table_values(int table[]) {
    for (int i = 0; i < SIZE; i++) {
        table[i] = 0; 
    }
}


void fill_freq_table( char text[], int freq_table[], const char dict_chars[], const int dict_position[]) {
    int i = 0; 
    int j = 0; 
    while (text[i] != '\0') {
        j = 0;
        while ( j < SIZE ) {
            if (text[i] == dict_chars[j]) {
                freq_table[dict_position[j]]++; 
                break; 
            }
            j++; 
        }
        i++; 
    }

}

void print_table_freq(int table[]) {
    for (int i = 0; i < SIZE; i++) {
        printf("\t%d = %d\n", i, table[i], i); 
    }
}
