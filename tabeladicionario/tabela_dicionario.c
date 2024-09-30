#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>  // Para usar a função toupper

// Definição do tamanho da tabela hash
#define TAMANHO_TABELA 26

// Estrutura para armazenar uma palavra e criar listas encadeadas
typedef struct Palavra {
    char palavra[50]; // Palavra armazenada
    struct Palavra* proximo; // Ponteiro para o próximo nó na lista
} Palavra;

// Tabela hash como um array de listas encadeadas
Palavra* tabelaHash[TAMANHO_TABELA];

// Função para converter uma letra em um código (0-25) baseado em 'A' = 0, 'Z' = 25
int letraParaCodigo(char letra) {
    letra = toupper(letra); // Converte para maiúscula
    return letra - 'A';     // Retorna o valor numérico da letra
}

// Função hash: gera o índice da tabela baseado nas duas primeiras letras da palavra
int funcaoHash(char* palavra) {
    int codigo1 = letraParaCodigo(palavra[0]);
    int codigo2 = letraParaCodigo(palavra[1]);

    // Concatenar os códigos das duas letras
    int codigoConcatenado = codigo1 * 100 + codigo2;
    return codigoConcatenado % TAMANHO_TABELA; // Calcula o índice da tabela hash
}

// Inicializa a tabela hash, colocando todas as posições como NULL
void inicializarTabela() {
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        tabelaHash[i] = NULL;
    }
}

// Função para inserir uma palavra na tabela hash
void inserirPalavra(char* palavra) {
    int indice = funcaoHash(palavra); // Calcula o índice na tabela

    // Cria uma nova estrutura para armazenar a palavra
    Palavra* novaPalavra = (Palavra*) malloc(sizeof(Palavra));
    strcpy(novaPalavra->palavra, palavra);
    novaPalavra->proximo = tabelaHash[indice]; // Insere no início da lista
    tabelaHash[indice] = novaPalavra;          // Atualiza a cabeça da lista
}

// Função para buscar uma palavra na tabela hash
Palavra* buscarPalavra(char* palavra) {
    int indice = funcaoHash(palavra); // Calcula o índice na tabela
    Palavra* atual = tabelaHash[indice];

    // Percorre a lista encadeada no índice correspondente
    while (atual != NULL) {
        if (strcmp(atual->palavra, palavra) == 0) {
            return atual; // Palavra encontrada
        }
        atual = atual->proximo;
    }
    return NULL; // Palavra não encontrada
}

// Função para excluir uma palavra da tabela hash
void excluirPalavra(char* palavra) {
    int indice = funcaoHash(palavra); // Calcula o índice na tabela
    Palavra* atual = tabelaHash[indice];
    Palavra* anterior = NULL;

    // Percorre a lista encadeada para encontrar a palavra
    while (atual != NULL) {
        if (strcmp(atual->palavra, palavra) == 0) {
            if (anterior == NULL) {
                // Se for o primeiro elemento da lista
                tabelaHash[indice] = atual->proximo;
            } else {
                // Ajusta o ponteiro do elemento anterior
                anterior->proximo = atual->proximo;
            }
            free(atual); // Libera a memória alocada para a palavra
            printf("Palavra '%s' excluída com sucesso.\n", palavra);
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("Palavra '%s' não encontrada.\n", palavra);
}

// Função para liberar a memória alocada para a tabela hash
void liberarMemoria() {
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        Palavra* atual = tabelaHash[i];
        while (atual != NULL) {
            Palavra* temp = atual;
            atual = atual->proximo;
            free(temp); // Libera cada palavra da lista
        }
    }
}

// Menu para interagir com o usuário
void menu() {
    int opcao;
    char palavra[50];

    do {
        printf("\n--- Sistema de Cadastro de Palavras ---\n");
        printf("1. Inserir Palavra\n");
        printf("2. Buscar Palavra\n");
        printf("3. Excluir Palavra\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer do teclado

        switch (opcao) {
            case 1:
                printf("Digite a palavra a ser inserida: ");
                fgets(palavra, 50, stdin);
                palavra[strcspn(palavra, "\n")] = '\0'; // Remove o '\n' do final
                inserirPalavra(palavra);
                break;
            case 2:
                printf("Digite a palavra a ser buscada: ");
                fgets(palavra, 50, stdin);
                palavra[strcspn(palavra, "\n")] = '\0';
                if (buscarPalavra(palavra) != NULL) {
                    printf("Palavra '%s' encontrada.\n", palavra);
                } else {
                    printf("Palavra '%s' não encontrada.\n", palavra);
                }
                break;
            case 3:
                printf("Digite a palavra a ser excluida: ");
                fgets(palavra, 50, stdin);
                palavra[strcspn(palavra, "\n")] = '\0';
                excluirPalavra(palavra);
                break;
            case 4:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 4);
}

int main() {
    inicializarTabela(); // Inicializa a tabela hash
    menu();              // Exibe o menu para o usuário
    liberarMemoria();    // Libera a memória alocada antes de sair
    return 0;
}
