// AO MODIFICAR O ARQUIVO DE ENTRADA 
// atualizar o valor das constantes SIZE_TEST e SIZE_LINE
    // SIZE_TEST - quantos números estão no arquivo  de entrada
    // SIZE_LINE - quantos caracteres tem o arquivo de entrada + 1 


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_TEST 45    // quantidade de números presentes no arquivo de entrada  
#define SIZE_LINE 125    // numero de caracteres da 1ª linha do arquivo de entada + 1 
#define SIZE_HASH 23    // tamanho da tabela 

typedef struct tlist
{
    int value; 
    struct tlist* next; 
} Tlist;

// cria nodo no final da lista      
Tlist* insertNode(Tlist* list, int newValue) {
    
    // criar novo nodo 
    Tlist* newNode; 
    newNode = (Tlist*) malloc(sizeof(Tlist));

    newNode->next = NULL;
    newNode->value = newValue; 

    // inserir nodo
        // se a lista estiver vazia, o nodo se torna a raiz da lista 
        // se não é inserido no final
    if (list == NULL) {
        list = newNode;
        return list; 
    } 
    else {
        Tlist* aux = list; 
        while (aux->next != NULL) aux = aux->next; 
        aux->next = newNode; 
        return list; 
    }

}

// imprime o parametro value dos nodos da lista encadeada 
void printTList(Tlist* list) {
    Tlist* aux = list; 
    if (aux == NULL) {
        printf("."); 
        return; 
    }

    while (aux != NULL) {
        printf("\t%d ", aux->value);
        aux = aux->next;
    }
}


// liberar meméria alocada para lista encadeada
void freeList(Tlist* list) {
    Tlist* aux; 

    while (list != NULL) {
        aux = list; 
        list = list->next;
        free(aux); 
    }
}

int hash(int num, int size_hash) {
    return num % size_hash; 
}

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


    char *num = strtok(line, ";");
    int count = 0; 

    while (num != NULL) {
        nums[count] = atoi(num); 
        count++; 

        num = strtok(NULL, ";"); 
    }

    // criar hash table 
    Tlist* hash_table[SIZE_HASH]; 

    for (int i = 0; i < SIZE_HASH; i++) {
        hash_table[i] = NULL; 
    }


    // inserir elementos na tabela
    printf("Insert...\n");
    int pos; 
    for (int i = 0 ; i < SIZE_TEST; i++) {
        pos = hash(nums[i], SIZE_HASH);
        hash_table[pos] = insertNode(hash_table[pos], nums[i]);
    }

    printf("\nFinal insert...\n");

    // printar tabela hash completa 
        printf("Tabela hash:");
    for (int i = 0; i < SIZE_HASH; i++) {
        printf("\n\t%d:", i); 
        printTList(hash_table[i]);
    }
    printf("\n");

    for (int i = 0; i < SIZE_HASH; i++) {
        freeList(hash_table[i]);
    }

    // printf("\n");
    // for (int i = 0; i < SIZE_TEST; i++) {
    //     printf("%d ", nums[i]); 
    // }

    return 0; 
}




    