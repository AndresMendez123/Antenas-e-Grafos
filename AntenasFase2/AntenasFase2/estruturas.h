/*!
 * @file estruturas.h
 * @author Andrés Mendez 
 * @date 2025-05-16
 * @brief Estruturas de dados e prototipos de funcoes para a Fase 2 - Grafos de Antenas.
 */

#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

 /**
  * @struct Aresta
  * @brief Representa uma ligacao entre duas antenas com a mesma frequ�ncia.
  */
typedef struct Aresta {
    struct Vertice* destino; /**< Ponteiro para o vertice de destino */
    struct Aresta* prox;     /**< Proxima aresta na lista de adjacencia */
} Aresta;

/**
 * @struct Vertice
 * @brief Representa uma antena no grafo, com posicao, frequencia e ligacoes.
 */
typedef struct Vertice {
    Aresta* adj;        /**< Lista de arestas (adjacencia) */
    char frequencia;    /**< Frequencia da antena */
    int visitado;       /**< Marcador de visitadoo (DFS/BFS) */
    int x, y;           /**< Coordenadas da antena na matriz */
} Vertice;

/**
 * @struct Grafo
 * @brief Estrutura que representa o grafo completo de antenas.
 */
typedef struct Grafo {
    int numVertices;     /**< Numero total de vertices (antenas) */
    Vertice* vertices;   /**< Array dinamico de vertices */
} Grafo;
void carregarGrafo(const char *nomeFicheiro, Grafo *g);
void criarArestas(Grafo *g);
void dfs(Vertice *v);
void bfs(Vertice *inicio);
void resetarVisitados(Grafo *g);
void caminhos(Vertice *origem, Vertice *destino, char trajeto[100][20], int nivel);
void intersecoes(Grafo *g, char f1, char f2);

#endif
