#include <stdio.h>
#include <stdlib.h>

#define MAX_vet 10

typedef struct Grafo {
  int num_vertices;
  int matriz_adj[MAX_vet][MAX_vet]; // Estrutura do grafo
} Grafo;

// Função que vai pegar o labirinto em char e tranformar em matriz adjacente
//  X == parede == 0 == caminho não percorrido;
//  0 == caminho == 1 == caminho percorrido;
//  E e S a ser discutido;
void *iniciar_grafo(Grafo *grafo, int num_vertices) {
  grafo->num_vertices = num_vertices;
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