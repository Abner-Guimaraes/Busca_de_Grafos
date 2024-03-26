#include <stdio.h>
#include <stdlib.h>

#define MAX_vet 10

//Matriz de adjacencia com Busca de largura(BFS);
//Djkstra;
//Qual o melhor método para não ir para o caminho errado;
//Começar em ponto especifico;

typedef struct Grafo {
  int num_vertices;
  int matriz_adj[MAX_vet][MAX_vet]; // Estrutura do grafo
} Grafo;

// Função que vai pegar o labirinto em char e tranformar em matriz adjacente
//  X == parede == 0 == caminho não percorrido;
//  0 == caminho == 1 == caminho percorrido;
//  E e S a ser discutido;
void *iniciar_Matriz_adjacencia(Grafo *grafo, int num_vertices) {
  grafo->num_vertices = num_vertices;
  int matriz[MAX_vet][MAX_vet];
  int linha = 0, coluna = 0;

  //colocar a matriz de char
  //caso tenha algum caractere do if entao na matriz é colocado 1 no indice !!!a mudar
  if( matriz[linha][coluna] == 'E' || matriz[linha][coluna] == 'S' || matriz[linha][coluna] == '0'){
    for(int i = 0; i< num_vertices; i++){
      for(int j = 0; j< num_vertices; j++){
        grafo->matriz_adj[i][j] = 1;
      }
    }
  }
    if(matriz[linha][coluna] == 'X'){
  for(int  i = 0; i < num_vertices; i++){
    for(int j = 0; j < num_vertices; j++){
      grafo->matriz_adj[i][j] = 0;
      }
    }
  }
}
// Função que faz a leitura do  arquivo e coloca caractere em uma matriz do tipo
// char para ser utilizado na verificação de labirinto;
char leitura_de_caracteres(FILE *arq, char labirinto[MAX_vet][MAX_vet]) {
  char caractere;
  int linha = 0, coluna = 0;

  while ((caractere = fgetc(arq)) != EOF) {
    if (caractere != '\n') {
      labirinto[linha][coluna] = caractere;
      coluna++;
    } else {
      coluna = 0;
      linha++;
    }
  }
}

int main(void) {
  char labirinto[MAX_vet][MAX_vet];

  FILE *arq = fopen("labirinto.txt", "r");
  if (arq == NULL) {
    printf("Erro ao abrir o arquivo!!!\n");
  } else {
    printf("Arquivo aberto para leitura!!!\n");
  }

  printf("Hello World\n");
  return 0;
}