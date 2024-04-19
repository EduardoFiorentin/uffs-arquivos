#include <stdio.h>

int main() {
    // Abrir o arquivo para leitura
    FILE *arquivo;
    arquivo = fopen("frase.txt", "r+");

    // Verificar se o arquivo foi aberto corretamente
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1; // Encerrar o programa com código de erro
    }

    // Ler a frase do arquivo e imprimir na tela
    char frase[100]; // Supondo que a frase tenha no máximo 1000 caracteres
    fgets(frase, sizeof(frase), arquivo);
    printf("%s\n", frase);

    // Fechar o arquivo
    fclose(arquivo);

    return 0; // Encerrar o programa com sucesso
}