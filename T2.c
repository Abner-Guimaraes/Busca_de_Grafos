#include <stdio.h>
#include <stdlib.h>

#define MAX_vet 10

// Matriz de adjacencia com Busca de largura(BFS);
// Qual o melhor método para não ir para o caminho errado;
// Começar em ponto especifico;

typedef struct {
  int num_vertices;
  int matriz_adj[MAX_vet][MAX_vet]; // Estrutura do grafo;
} Grafo;

typedef struct {
  int linha;
  int coluna;
} Coordenada; // struct para especificar o ponto de inicio e fim do labirinto;

// criando estruturas para fila para utilizar o metodo BFS;
typedef struct no {
  int item;
  struct no *proximo;
} No;

typedef struct fila {
  No *inicio;
  No *fim;
} Fila;

// Função que faz a leitura do  arquivo e cria a matriz de adjacencia;
// é nessesario utilizar debugger para analisar essa função;
void iniciar_matriz_adjacencia(Grafo *grafo, FILE *arq) {
  char caractere;
  int linha = 0, coluna = 0;
  Coordenada coordenada_inicio;
  Coordenada coordenada_fim;

  while ((caractere = fgetc(arq)) != EOF) {
    if (caractere != '\n') {
      if (caractere == 'E' || caractere == 'S' || caractere == '0') {
        grafo->matriz_adj[linha][coluna] = 1;
        coluna++;
        if (caractere == 'E') {
          coordenada_inicio.linha = linha;
          coordenada_inicio.coluna = coluna;
        }
        if (caractere == 'S') {
          coordenada_fim.linha = linha;
          coordenada_fim.coluna = coluna;
        }
      } else if (caractere == 'X') {
        grafo->matriz_adj[linha][coluna] = 0;
        coluna++;
      } else {
        linha++;
        coluna = 0;
      }
    }
  }
}

void iniciar_fila(Fila *fila) {
  fila->inicio = NULL;
  fila->fim = NULL;
}

int lista_vazia(Fila *fila) { return (fila->inicio == NULL); }

void *inserir_V_fila(Fila *fila, int item) {}
No *remover_V_fila(Fila *fila) {}

int main(void) {

  Grafo *labirinto;

  FILE *arq = fopen("labirinto1.txt", "r");
  if (arq == NULL) {
    printf("Erro ao abrir o arquivo!!!\n");
  } else {
    printf("Arquivo aberto para leitura!!!\n");
  }

  labirinto = (Grafo *)malloc(sizeof(Grafo));
  if (labirinto == NULL) {
    printf("Erro ao alocar memoria na matriz\n");
    fclose(arq);
    return 1;
  }

  iniciar_matriz_adjacencia(labirinto, arq);

  printf("Hello World\n");

  free(labirinto);
  fclose(arq);

  return 0;
}