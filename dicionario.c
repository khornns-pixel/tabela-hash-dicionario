#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_HASH 11

typedef struct Node {
    char palavra[50];
    char definicao[200];
    struct Node* proximo;
} Node;

typedef struct {
    Node* tabelas[TAM_HASH];
} TabelaHash;

int funcaoHash(const char* palavra) {
    unsigned int hash = 0;
    for (int i = 0; palavra[i] != '\0'; i++) {
        hash = hash * 31 + palavra[i];
    }
    return hash % TAM_HASH;
}

void inserir(TabelaHash* th, const char* palavra, const char* definicao) {
    int indice = funcaoHash(palavra);
    
    Node* atual = th->tabelas[indice];
    while (atual != NULL) {
        if (strcmp(atual->palavra, palavra) == 0) {
            strcpy(atual->definicao, definicao);
            printf("Palavra '%s' atualizada com nova definicao.\n", palavra);
            return;
        }
        atual = atual->proximo;
    }

    Node* novoNode = (Node*)malloc(sizeof(Node));
    if (novoNode == NULL) {
        printf("Erro de alocacao de memoria!\n");
        return;
    }
    strcpy(novoNode->palavra, palavra);
    strcpy(novoNode->definicao, definicao);
    
    novoNode->proximo = th->tabelas[indice];
    th->tabelas[indice] = novoNode;
    printf("'%s' inserida com sucesso no indice %d.\n", palavra, indice);
}

Node* buscar(TabelaHash* th, const char* palavra) {
    int indice = funcaoHash(palavra);
    Node* atual = th->tabelas[indice];

    while (atual != NULL) {
        if (strcmp(atual->palavra, palavra) == 0) {
            return atual;
        }
        atual = atual->proximo;
    }
    return NULL;
}

void remover(TabelaHash* th, const char* palavra) {
    int indice = funcaoHash(palavra);
    Node* atual = th->tabelas[indice];
    Node* anterior = NULL;

    while (atual != NULL && strcmp(atual->palavra, palavra) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Palavra '%s' nao encontrada para remocao.\n", palavra);
        return;
    }

    if (anterior == NULL) {
        th->tabelas[indice] = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual);
    printf("Palavra '%s' removida com sucesso.\n", palavra);
}

void exibirTabela(TabelaHash* th) {
    printf("\n===== EXIBIÇÃO DA TABELA HASH =====\n");
    for (int i = 0; i < TAM_HASH; i++) {
        printf("[%2d]: ", i);
        Node* atual = th->tabelas[i];
        if (atual == NULL) {
            printf("NULL\n");
        } else {
            while (atual != NULL) {
                printf("(%s: %s) -> ", atual->palavra, atual->definicao);
                atual = atual->proximo;
            }
            printf("NULL\n");
        }
    }
    printf("======================================\n");
}

void exibirEstatisticas(TabelaHash* th) {
    int totalElementos = 0;
    int totalColisoes = 0;
    int maiorLista = 0;

    for (int i = 0; i < TAM_HASH; i++) {
        int elementosNaLista = 0;
        Node* atual = th->tabelas[i];
        
        while (atual != NULL) {
            elementosNaLista++;
            atual = atual->proximo;
        }

        totalElementos += elementosNaLista;

        if (elementosNaLista > 1) {
            totalColisoes += (elementosNaLista - 1);
        }

        if (elementosNaLista > maiorLista) {
            maiorLista = elementosNaLista;
        }
    }

    float fatorCarga = (float)totalElementos / TAM_HASH;

    printf("\n===== ESTATÍSTICAS DA TABELA =====\n");
    printf("• Quantidade de elementos: %d\n", totalElementos);
    printf("• Quantidade de colisoes: %d\n", totalColisoes);
    printf("• Fator de carga: %.2f\n", fatorCarga);
    printf("• Maior lista encadeada: %d\n", maiorLista);
    printf("=====================================\n");
}

void limparTabela(TabelaHash* th) {
    for (int i = 0; i < TAM_HASH; i++) {
        Node* atual = th->tabelas[i];
        while (atual != NULL) {
            Node* temp = atual;
            atual = atual->proximo;
            free(temp);
        }
        th->tabelas[i] = NULL;
    }
}

int main() {
    TabelaHash th;
    for (int i = 0; i < TAM_HASH; i++) {
        th.tabelas[i] = NULL;
    }

    int opcao;
    char pal[50], def[200];
    Node* buscaResultado;

    do {
        printf("\n--- DICIONÁRIO HASH ---\n");
        printf("1. Inserir Palavra\n");
        printf("2. Buscar Palavra\n");
        printf("3. Remover Palavra\n");
        printf("4. Exibir Tabela Hash\n");
        printf("5. Exibir Estatisticas\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
            case 1:
                printf("Digite a palavra: ");
                fgets(pal, 50, stdin); pal[strcspn(pal, "\n")] = 0;
                printf("Digite a definicao: ");
                fgets(def, 200, stdin); def[strcspn(def, "\n")] = 0;
                inserir(&th, pal, def);
                break;
            case 2:
                printf("Digite a palavra para buscar: ");
                fgets(pal, 50, stdin); pal[strcspn(pal, "\n")] = 0;
                buscaResultado = buscar(&th, pal);
                if (buscaResultado != NULL) {
                    printf("🔍 Encontrado! %s: %s\n", buscaResultado->palavra, buscaResultado->definicao);
                } else {
                    printf("Palavra nao encontrada.\n");
                }
                break;
            case 3:
                printf("Digite a palavra para remover: ");
                fgets(pal, 50, stdin); pal[strcspn(pal, "\n")] = 0;
                remover(&th, pal);
                break;
            case 4:
                exibirTabela(&th);
                break;
            case 5:
                exibirEstatisticas(&th);
                break;
            case 0:
                printf("Encerrando e liberando espaco de memoria...\n");
                limparTabela(&th);
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while(opcao != 0);

    return 0;
}

