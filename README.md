# Busca_de_Grafos
Trabalho de Grafos em estruturas de dados .c/c++

"Para o nosso trabalho de Matriz de Adjacência em linguagem C, estamos criando um programa que representa um labirinto usando uma matriz. Cada célula da matriz corresponde a uma parte do labirinto e suas conexões são indicadas pelos valores na matriz. Nosso objetivo é desenvolver um código capaz de resolver problemas relacionados ao labirinto, como encontrar caminhos entre dois pontos ou verificar a existência de um caminho válido da entrada para a saída."

# Primeiro código: Algoritmo BFS com Matriz de Adjacência

Este repositório contém uma implementação em C do algoritmo BFS (Busca em Largura) utilizando uma matriz de adjacência. Este algoritmo é uma forma eficiente de encontrar o caminho mais curto em um grafo não ponderado.

## Matriz de Adjacência:

A matriz de adjacência é uma estrutura de dados frequentemente utilizada para representar grafos. Em um grafo não direcionado, ela é uma matriz quadrada onde cada linha e coluna representam um vértice e os elementos indicam se existe uma aresta entre os vértices correspondentes. Para grafos direcionados, a matriz pode ser assimétrica. Se o grafo for ponderado, os elementos da matriz podem armazenar o peso das arestas.

## BFS (Busca em Largura):

A busca em largura é um algoritmo de busca em grafos que explora todos os vértices em um mesmo nível antes de prosseguir para os vértices do próximo nível. Este algoritmo é implementado tipicamente com o auxílio de uma fila, que armazena os vértices a serem visitados. Começando de um vértice inicial, o BFS visita todos os vértices adjacentes a ele, marcando-os como visitados e os colocando na fila. Esse processo continua até que todos os vértices acessíveis sejam visitados.

## Implementação:

A implementação neste repositório demonstra como usar uma matriz de adjacência para representar um grafo e como aplicar o algoritmo BFS para percorrer o grafo e encontrar o caminho mais curto entre dois vértices.

Sinta-se à vontade para explorar o código e contribuir para melhorias!

# Segundo código: Algoritmo DFS com Matriz de adjacência

Este repositório contém uma implementação em C do algoritmo DFS (Busca em Profundidade) utilizando uma matriz de adjacência. Este algoritmo é uma abordagem eficaz para explorar grafos e encontrar soluções para problemas de conectividade, busca de caminhos e outras análises de grafos. Ao contrário da busca em largura (BFS), que explora níveis de vizinhança de forma sistemática, o DFS mergulha o mais fundo possível em um ramo do grafo antes de retroceder para explorar outros ramos. Isso o torna útil para tarefas como identificação de ciclos, componentes conectados e ordenação topológica. Esta implementação oferece uma maneira concisa e eficiente de realizar buscas em profundidade em grafos representados por uma matriz de adjacência em linguagem C.

## Implementação:

A implementação neste repositório demonstra como usar uma matriz de adjacência para representar um grafo e como aplicar o algoritmo DFS para percorrer o grafo e explorar sua estrutura em profundidade. Em vez de encontrar o caminho mais curto entre dois vértices, o algoritmo DFS busca explorar o grafo de forma abrangente, mergulhando profundamente em cada ramificação antes de retroceder. Isso é útil para identificar ciclos, componentes conectados e outras características do grafo. O código fornece uma implementação clara e eficiente do algoritmo DFS em linguagem C.