#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FILA 5

// Tipos de peças permitidas
char tipos[] = {'I', 'O', 'T', 'L'};

// Estrutura da peça
typedef struct {
    char tipo;
    int id;
} Peca;

// Estrutura da fila circular
typedef struct {
    Peca itens[MAX_FILA];
    int frente;
    int tras;
    int tamanho;
    int proximoID;
} Fila;

// Inicializa a fila
void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = -1;
    f->tamanho = 0;
    f->proximoID = 1;
}

// Verifica se a fila está cheia
int filaCheia(Fila *f) {
    return f->tamanho == MAX_FILA;
}

// Verifica se a fila está vazia
int filaVazia(Fila *f) {
    return f->tamanho == 0;
}

// Gera uma nova peça com tipo aleatório e ID único
Peca gerarPeca(Fila *f) {
    Peca nova;
    nova.tipo = tipos[rand() % 4];
    nova.id = f->proximoID++;
    return nova;
}

// Insere uma peça ao final da fila
void enfileirar(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("⚠️  Fila cheia! Não é possível adicionar a peça %c (ID %d).\n", p.tipo, p.id);
        return;
    }
    f->tras = (f->tras + 1) % MAX_FILA;
    f->itens[f->tras] = p;
    f->tamanho++;
    printf("✅ Peça %c (ID %d) adicionada à fila.\n", p.tipo, p.id);
}

// Remove a peça da frente da fila
void jogarPeca(Fila *f) {
    if (filaVazia(f)) {
        printf("⚠️  Fila vazia! Nenhuma peça para jogar.\n");
        return;
    }
    Peca p = f->itens[f->frente];
    f->frente = (f->frente + 1) % MAX_FILA;
    f->tamanho--;
    printf("🎮 Peça %c (ID %d) jogada!\n", p.tipo, p.id);
}

// Exibe o estado atual da fila
void exibirFila(Fila *f) {
    printf("\n📦 Fila de peças (%d/%d):\n", f->tamanho, MAX_FILA);
    if (filaVazia(f)) {
        printf("  [vazia]\n");
        return;
    }
    for (int i = 0; i < f->tamanho; i++) {
        int idx = (f->frente + i) % MAX_FILA;
        printf("  → Peça %c (ID %d)\n", f->itens[idx].tipo, f->itens[idx].id);
    }
    printf("\n");
}

// Menu de opções
void menu() {
    printf("Escolha uma ação:\n");
    printf("1 - Inserir nova peça\n");
    printf("2 - Jogar peça\n");
    printf("3 - Visualizar fila\n");
    printf("0 - Sair\n");
    printf("Opção: ");
}

int main() {
    Fila fila;
    inicializarFila(&fila);
    srand(time(NULL));

    int opcao;

    do {
        menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                Peca nova = gerarPeca(&fila);
                enfileirar(&fila, nova);
                break;
            }
            case 2:
                jogarPeca(&fila);
                break;
            case 3:
                exibirFila(&fila);
                break;
            case 0:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}