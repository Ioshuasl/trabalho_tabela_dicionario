#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define N 26 

typedef struct no {
    char palavra[50];
    struct no* prox;
} No;

int hash(char* palavra) {
    char primeira_letra = tolower(palavra[0]);
    char segunda_letra = tolower(palavra[1]);

    int codigo = (primeira_letra - 'a') * 100 + (segunda_letra - 'a');
    return codigo % 26;
}


void inserir(No* tabela[], char* palavra) {
    int pos = hash(palavra);

    No* novo = (No*) malloc(sizeof(No));
    strcpy(novo->palavra, palavra);
    novo->prox = tabela[pos];
    tabela[pos] = novo;

    printf("Palavra '%s' inserida na posição %d\n", palavra, pos);
}

No* buscar(No* tabela[], char* palavra) {
    int pos = hash(palavra);
    No* atual = tabela[pos];

    while (atual != NULL) {
        if (strcmp(atual->palavra, palavra) == 0) {
            printf("Palavra '%s' encontrada na posição %d\n", palavra, pos);
            return atual;
        }
        atual = atual->prox;
    }
    printf("Palavra '%s' não encontrada\n", palavra);
    return NULL;
}

void remover(No* tabela[], char* palavra) {
    int pos = hash(palavra);
    No* atual = tabela[pos];
    No* anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->palavra, palavra) == 0) {
            if (anterior == NULL) {
                tabela[pos] = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            free(atual);
            printf("Palavra '%s' removida da posição %d\n", palavra, pos);
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }
    printf("Palavra '%s' não encontrada para remoção\n", palavra);
}

void inicializarTabela(No* tabela[]) {
    for (int i = 0; i < N; i++) {
        tabela[i] = NULL;
    }
}

int main() {
    No* tabela[N];
    inicializarTabela(tabela);

    int opcao;
    char palavra[50];

    do {
        printf("\n1. Inserir palavra\n");
        printf("2. Buscar palavra\n");
        printf("3. Remover palavra\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite a palavra para inserir: ");
                scanf("%s", palavra);
                inserir(tabela, palavra);
                break;

            case 2:
                printf("Digite a palavra para buscar: ");
                scanf("%s", palavra);
                buscar(tabela, palavra);
                break;

            case 3:
                printf("Digite a palavra para remover: ");
                scanf("%s", palavra);
                remover(tabela, palavra);
                break;

            case 4:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while (opcao != 4);

    return 0;
}
