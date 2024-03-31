#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_vet 10
#define BRANCO 0
#define CINZA 1
#define PRETO 2

// Matriz de adjacencia com Busca de largura(BFS) e Busca em Profundidade (DFS);
// Qual o melhor método para não ir para o caminho errado;
// Começar em ponto especifico;

typedef struct coordenada {
  int linha;
  int coluna;
} Coordenada; // Struct para especificar o ponto de inicio e fim do labirinto;


typedef struct {
  int num_vertices;
  int **matriz_adj; // Estrutura do grafo;
  int matriz_ver[MAX_vet][MAX_vet]; // Matriz de vertices;
  Coordenada *listaVertice;
  Coordenada coordenada_inicio;
  Coordenada coordenada_fim; // Coordenada de E e S;

} Grafo;

// Criando estruturas para fila para utilizar o metodo BFS;
typedef struct no {
  int vertice_linha;
  int vertice_coluna;
  struct no *proximo;
} No;

typedef struct fila {
  No *inicio;
  No *fim;
} Fila;


void inserir_pilha(No **topo, No *novo_no)
{
    novo_no->proximo = (*topo);
    *topo = novo_no;
}


No *remover_pilha(No **topo)
{
    No *tmp = NULL;
    if (*topo != NULL)
    {
        tmp = *topo;
        (*topo) = (*(*topo)).proximo;
    }
    return tmp;
}

void imprimir(No *topo)
{
    if (topo == NULL)
    {
        return;
    }

    imprimir(topo->proximo);    
    printf("%d,%d", topo->vertice_linha, topo->vertice_coluna);
    printf("\n");
    
}

//
/* void imprimir(No *topo)
{
    if (topo == NULL)
    {
        printf("pilha vazia");
        return;
    }

    
    while (topo != NULL)
    {
        printf("%d,%d", topo->vertice_linha, topo->vertice_coluna);
        topo = topo->proximo;
        if (topo != NULL)
            printf("\n");
    }
} */

// Função que faz a leitura do  arquivo e cria a matriz de adjacencia;
// é necessário utilizar debugger para analisar essa função;
void verificacao_vertice(Grafo *grafo, FILE *arq) {
  char caractere;
  int linha = 0, coluna = 0;
  grafo->num_vertices = 0;
  Coordenada coordenada_inicio;
  Coordenada coordenada_fim;

  while ((caractere = fgetc(arq)) != EOF) {
    if (caractere == 'E' || caractere == 'S' || caractere == '0') {
      grafo->matriz_ver[linha][coluna] = 1;
      if (caractere == 'E') {
        grafo->coordenada_inicio.linha = linha;
        grafo->coordenada_inicio.coluna = coluna;
      }
      if (caractere == 'S') {
        grafo->coordenada_fim.linha = linha;
        grafo->coordenada_fim.coluna = coluna;
      }
      grafo->num_vertices++;
      coluna++;
    } else if (caractere == 'X') {
      grafo->matriz_ver[linha][coluna] = 0;
      coluna++;

    } else {
      linha++;
      coluna = 0;
    }
  }
}

void inicializar_matriz_adjacencia(Grafo *grafo, int num_vertices) {
  grafo->num_vertices = num_vertices;
  grafo->matriz_adj = (int **) malloc(sizeof(int *) * num_vertices);
  int i;
  for (i = 0; i < num_vertices; i++)
    grafo->matriz_adj[i] = (int*)malloc(num_vertices * sizeof(int));
  for (i = 0; i < MAX_vet; i++) {
    for (int j = 0; j < MAX_vet; j++) {
      grafo->matriz_adj[i][j] = 0;
    }
  }
}


void construir_matriz_adjacencia(Grafo *grafo) {
  int num_vertices = grafo->num_vertices;
  
  for (int i = 0; i < num_vertices; i++) {
    for (int j = 0; j < num_vertices; j++) {

      if (&grafo->listaVertice[i] == &grafo->listaVertice[j]) {
        grafo->matriz_adj[i][j] = 0;
      } else {
        // verifica se conectado em cima
        if (grafo->listaVertice[j].linha - 1 == grafo->listaVertice[i].linha && grafo->listaVertice[j].coluna == grafo->listaVertice[i].coluna) {
            grafo->matriz_adj[i][j] = 1;
        }
        // verifica se conectado em baixo
        else if (grafo->listaVertice[j].linha + 1 == grafo->listaVertice[i].linha && grafo->listaVertice[j].coluna == grafo->listaVertice[i].coluna) {
          grafo->matriz_adj[i][j] = 1;
        }
        // verifica se conectado na direita
        else if (grafo->listaVertice[j].coluna + 1 == grafo->listaVertice[i].coluna && grafo->listaVertice[j].linha == grafo->listaVertice[i].linha) {
          grafo->matriz_adj[i][j] = 1;

        }
        // verifica se conectado na esquerda
        else if (grafo->listaVertice[j].coluna - 1 == grafo->listaVertice[i].coluna && grafo->listaVertice[j].linha == grafo->listaVertice[i].linha) {
          grafo->matriz_adj[i][j] = 1;
        } else {
          grafo->matriz_adj[i][j] = 0;
        }
      }
    }
  }
}


void criar_listaVertice(Grafo *grafo) {
  int num_vertices = grafo->num_vertices;
  grafo->listaVertice = (Coordenada*) malloc(sizeof(Coordenada) * num_vertices);
  int indexVertices = 0;
  for (int i = 0; i < MAX_vet; i++) {
    for (int j = 0; j < MAX_vet; j++) {
      if (grafo->matriz_ver[i][j] == 1) {
        grafo->listaVertice[indexVertices].linha = i;
        grafo->listaVertice[indexVertices].coluna = j;
        indexVertices++;
      }
    }
  }
  construir_matriz_adjacencia(grafo);
}

bool visitaP(Grafo *grafo, int u, int cor[], No *caminho) {
    cor[u] = CINZA;


    No *vertice = malloc(sizeof(No));
    vertice->vertice_linha = grafo->listaVertice[u].linha;
    vertice->vertice_coluna = grafo->listaVertice[u].coluna;
    inserir_pilha(&caminho, vertice);

    if(grafo->listaVertice[u].linha == grafo->coordenada_fim.linha && grafo->listaVertice[u].coluna == grafo->coordenada_fim.coluna){
      imprimir(caminho);
      return true;
    }
    
    for (int v = 0; v < grafo->num_vertices; v++) {
        if (grafo->matriz_adj[u][v] == 1 && cor[v] == BRANCO) {
            visitaP(grafo, v, cor, caminho);
        }
    }

    cor[u] = PRETO;

    remover_pilha(&caminho);
   
}

void profundidade(Grafo *grafo){
  int num_vertices = grafo->num_vertices;
  int cor[num_vertices];
  No *caminho = NULL;
  int u;
  for(u = 0; u < num_vertices; u++){
    cor[u] = BRANCO;
  }

  for (u = grafo->coordenada_inicio.linha; u < num_vertices; u++)
  {
    if(cor[u] == BRANCO){
      visitaP(grafo, u, cor, caminho);
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

void *inserir_V_fila(Fila *fila, int vertice_linha, int vertice_coluna) {
  No *novo_no = (No *)malloc(sizeof(No)); // criação de um novo nó com vertice;

  novo_no->proximo = NULL;
  // novo_no->vertice_linha = item; recebimento de vertice linha;
  // novo_no->vertice_coluna = item; recebimento de vertice coluna;

  if (lista_vazia(fila)) {
    fila->inicio = novo_no;
    fila->fim = novo_no;
    novo_no->proximo = NULL;
  } else {
    fila->fim->proximo = novo_no;
    novo_no->proximo = NULL;
    fila->fim = novo_no;
  }
}

No *remover_V_fila(Fila *fila) {
  if (lista_vazia(fila)) {
    return NULL;
  } else {
    No *aux = fila->inicio;
    fila->inicio = fila->inicio->proximo;
    free(aux);
  }
}

int BFS_Busca_largura(Fila *fila, Grafo *grafo) {
  int vetor_no [MAX_vet];
  
  iniciar_fila(fila); //Começa a fila vazia
  
  inserir_V_fila(fila, grafo->coordenada_inicio.linha, grafo->coordenada_inicio.coluna); //Coloca a coordenada de E;

  while (!lista_vazia(fila)){

    
    
  }
}

int main(void) {

  Grafo *labirinto;

  FILE *arq = fopen("Labirintos/labirinto1.txt", "r");
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
  


  inicializar_matriz_adjacencia(labirinto, labirinto->num_vertices);
  criar_listaVertice(labirinto);
  profundidade(labirinto);

  //printf("Hello World\n");

  free(labirinto);
  fclose(arq);

  return 0;
}