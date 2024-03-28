#include <stdio.h>
#include <stdlib.h>

#define MAX_vet 10

// Matriz de adjacencia com Busca de largura(BFS);
// Qual o melhor método para não ir para o caminho errado;
// Começar em ponto especifico;

typedef struct coordenada{
  int linha;
  int coluna;
} Coordenada; // Struct para especificar o ponto de inicio e fim do labirinto;

typedef struct {
  int num_vertices;
  int matriz_ver[MAX_vet][MAX_vet]; // Estrutura do grafo;
  Coordenada coordenada_inicio;
  Coordenada coordenada_fim; // Coordenada de E e S;

  Coordenada anterior;
  Coordenada superior;
} Grafo;

// Criando estruturas para fila para utilizar o metodo BFS;
typedef struct no {
  int vertice;
  struct no *proximo;
} No;

typedef struct fila {
  No *inicio;
  No *fim;
} Fila;

// Função que faz a leitura do  arquivo e cria a matriz de adjacencia;
// é nessesario utilizar debugger para analisar essa função;
void verificacao_vertice(Grafo *grafo, FILE *arq) {
  char caractere;
  int linha = 0, coluna = 0;
  grafo->num_vertices = 0;
  Coordenada coordenada_inicio;
  Coordenada coordenada_fim;

  while ((caractere = fgetc(arq)) != EOF) {
      if (caractere == 'E' || caractere == 'S' || caractere == '0') {
        grafo->matriz_ver[linha][coluna] = 1;
        coluna++;
        if (caractere == 'E') {
          grafo->coordenada_inicio.linha = linha;
          grafo->coordenada_inicio.coluna = coluna;
        }
        if (caractere == 'S') {
          grafo->coordenada_fim.linha = linha;
          grafo->coordenada_fim.coluna = coluna;
        }
        grafo->num_vertices++;
      } else if (caractere == 'X') {
        grafo->matriz_ver[linha][coluna] = 0;
        coluna++;

      } else {
        linha++;
        coluna = 0;
            }
        }
    }


void iniciar_fila(Fila *fila) {
  fila->inicio = NULL;
  fila->fim = NULL;
}

int lista_vazia(Fila *fila) {
  return (fila->inicio == NULL);
}

void *inserir_V_fila(Fila *fila, int item) {
  No *novo_no = (No *)malloc(sizeof(No)); //criação de um novo nó com vertice;

  novo_no->proximo = NULL;
  //novo_no->vertice = item; recebimento de vertice; como
  
  if(lista_vazia(fila)){
    fila->inicio = novo_no;
    fila->fim = novo_no;
    novo_no->proximo = NULL;
  }else{
    fila->fim->proximo = novo_no;
    novo_no->proximo = NULL;
    fila->fim = novo_no;
  }
}

No *remover_V_fila(Fila *fila){
  if(lista_vazia(fila)){
    return NULL;
  }else{
    No *aux = fila->inicio;
    fila->inicio = fila->inicio->proximo;
    free(aux);
  }
}

int main(void) {

  Grafo *labirinto;

  FILE *arq = fopen("labirinto2.txt", "r");
  if (arq == NULL) {
    printf("Erro ao abrir o arquivo!!!\n");
    return 1;
  } else {
    printf("Arquivo aberto para leitura!!!\n");
  }

  labirinto = (Grafo *)malloc(sizeof(Grafo));
  if (labirinto == NULL) {
    printf("Erro ao alocar memoria na matriz\n");
    fclose(arq);
    return 1;
  }

  verificacao_vertice(labirinto, arq);

  printf("Hello World\n");

  free(labirinto);
  fclose(arq);

  return 0;
}
