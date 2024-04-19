// fazer um progrmana que leia o conteúdo de um arquivo de texto, imprima na tela e depois peça uma nova frase e salve no arquivo

#include <stdio.h>

int main() {
    // Abrir o arquivo para leitura
    FILE *arquivo;
    arquivo = fopen("frase.txt", "r");

    // Verificar se o arquivo foi aberto corretamente
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1; // Encerrar o programa com código de erro
    }

    // Ler a frase do arquivo e imprimir na tela
    char frase[1000]; // Supondo que a frase tenha no máximo 1000 caracteres
    fgets(frase, sizeof(frase), arquivo);
    printf("Frase do arquivo: %s\n", frase);
    
    
    arquivo = fopen("frase.txt", "w");

    char novaFrase[100];
    printf("Digite uma nova frase para adicionar ao arquivo: ");
    fgets(novaFrase, sizeof(novaFrase), stdin);

    // Gravar a nova frase no arquivo
    fprintf(arquivo, "%s", novaFrase);

    fclose(arquivo);

    return 0; // Encerrar o programa com sucesso
}