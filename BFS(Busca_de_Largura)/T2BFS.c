#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_vet 10
#define BRANCO 0
#define CINZA 1
#define PRETO 2

/*+-----------------------------------------------------------+
 | UNIFAL – Universidade Federal de Alfenas.                   |
 | BACHARELADO EM CIENCIA DA COMPUTACAO.                       |
 | Trabalho: Busca de Grafos                                   |
 | Disciplina: Algoritmos e Estrutura de Dados II – Pratica    |
 | Professor: Iago Augusto Carvalho                            |
 | Aluno(s): Abner Gomes Guimarães - Felipe Araújo Correia     |
 | Diogo da Silva Moreira - Gustavo Marcelino Izidoro          |
 | Marcelo Bernardino da Silva Junior - Barbara Lima Marques   |
 | Data: 01/04/2023                                            |
 +-------------------------------------------------------------+
*/

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
    printf("%d,%d", topo->vertice_coluna, MAX_vet - 1 - topo->vertice_linha);
    printf("\n");
    
}



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
        // verifica se conectado em cima;
        if (grafo->listaVertice[j].linha - 1 == grafo->listaVertice[i].linha && grafo->listaVertice[j].coluna == grafo->listaVertice[i].coluna) {
            grafo->matriz_adj[i][j] = 1;
        }
        // verifica se conectado em baixo;
        else if (grafo->listaVertice[j].linha + 1 == grafo->listaVertice[i].linha && grafo->listaVertice[j].coluna == grafo->listaVertice[i].coluna) {
          grafo->matriz_adj[i][j] = 1;
        }
        // verifica se conectado na direita;
        else if (grafo->listaVertice[j].coluna + 1 == grafo->listaVertice[i].coluna && grafo->listaVertice[j].linha == grafo->listaVertice[i].linha) {
          grafo->matriz_adj[i][j] = 1;

        }
        // verifica se conectado na esquerda;
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

void iniciar_fila(Fila *fila) {
  fila->inicio = NULL;
  fila->fim = NULL;
}

void *inserir_V_fila(Fila *fila,int vertice) {
  No *novo_vertice = (No*) malloc(sizeof(No));
  novo_vertice->vertice_linha = vertice; 

  if (fila->inicio == NULL) {
    fila->inicio = novo_vertice;
    fila->fim = novo_vertice;
    novo_vertice->proximo = NULL;
  } else {
    fila->fim->proximo = novo_vertice;
    novo_vertice->proximo = NULL;
    fila->fim = novo_vertice;
  }
}

int remover_V_fila(Fila *fila) {
  if (fila->inicio == NULL) {
    return -1;
  } else {
    No *aux = fila->inicio;
    fila->inicio = fila->inicio->proximo;
    return aux->vertice_linha;
    free(aux);
  }
}

bool visitaL(Grafo *grafo, int s, bool *explorados,int *distancia, Fila *fila) {
    // Marca o vértice inicial como explorado e o adiciona à fila
    explorados[s] = true;
    distancia[s] = 0;
    inserir_V_fila(fila, s);

    while (fila->inicio != NULL) {
        // Remove o primeiro vértice da fila
        int u = remover_V_fila(fila);
        
        // Percorre todos os vértices adjacentes a u
        for (int v = 0; v < grafo->num_vertices; v++) {
            // Verifica se v é adjacente a u e se ainda não foi exploradov
            if (grafo->matriz_adj[u][v] && !explorados[v]) {
                // Marca v como explorado e o adiciona à fila
                explorados[v] = true;
                distancia[v] = distancia[u] + 1;
                inserir_V_fila(fila, v);
            }
        }
    }
    
     return true;
}

int BFS_Busca_largura(Grafo *grafo) {
    bool explorados[grafo->num_vertices];
    int distancia[grafo->num_vertices];
    Fila fila;
    iniciar_fila(&fila);

    // Inicializa todos os vértices como não explorados
    for (int u = 0; u < grafo->num_vertices; u++) {
        explorados[u] = false;
        distancia[u] = -1;
    }

    // Começa a busca em largura a partir do vértice de origem
    int origem = grafo->coordenada_inicio.linha;
    visitaL(grafo, origem, explorados,distancia, &fila);
    
    for (int i = 0; i < grafo->num_vertices; i++) {
        if(distancia[i] >= distancia[i-1] || i == 0)
            printf("%d,%d\n", grafo->listaVertice[i].coluna, MAX_vet - 1 - grafo->listaVertice[i].linha);
    }
}



int main(void) {

  Grafo *labirinto;

   char filename[1000];
  printf("Digite o nome do arquivo: ");
  scanf("%s", filename);
  strcat(filename, ".txt");
  
  FILE *arq = fopen(filename, "r");
    
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
  BFS_Busca_largura(labirinto);

  

  free(labirinto);
  fclose(arq);

  return 0;
}