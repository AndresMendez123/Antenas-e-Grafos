/*!
 * @file funcoes.c
 * @author Andrés Mendez 
 * @date 2025-05-16
 * @brief Funções para manipulação de grafos na Fase 2 (grafos de antenas).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"

#define MAX_LINHA 200
#define MAX_VERTICES 1000

#pragma warning (disable:4996)

 /**
  * @brief Carrega um grafo a partir de um ficheiro com uma matriz de antenas.
  * @param nomeFicheiro Nome do ficheiro com a matriz.
  * @param g Ponteiro para o grafo a preencher.
  */
void carregarGrafo(const char* nomeFicheiro, Grafo* g) {
    FILE* fp = fopen(nomeFicheiro, "r");
    if (!fp) {
        printf("Erro ao abrir o ficheiro.\n");
        exit(1);
    }

    char linha[MAX_LINHA];
    int linhaAtual = 0;
    int totalVertices = 0;
    Vertice* tempVertices = malloc(MAX_VERTICES * sizeof(Vertice));

    while (fgets(linha, sizeof(linha), fp)) {
        if (linha[0] >= '0' && linha[0] <= '9' && linha[1] == '\n') continue;

        for (int col = 0; linha[col] != '\0' && linha[col] != '\n'; col++) {
            if (linha[col] != '.') {
                tempVertices[totalVertices].frequencia = linha[col];
                tempVertices[totalVertices].x = linhaAtual;
                tempVertices[totalVertices].y = col;
                tempVertices[totalVertices].visitado = 0;
                tempVertices[totalVertices].adj = NULL;
                totalVertices++;
            }
        }
        linhaAtual++;
    }

    fclose(fp);

    g->numVertices = totalVertices;
    g->vertices = malloc(totalVertices * sizeof(Vertice));
    for (int i = 0; i < totalVertices; i++) {
        g->vertices[i] = tempVertices[i];
    }

    free(tempVertices);
}

/**
 * @brief Cria arestas entre vértices de mesma frequência no grafo.
 * @param g Ponteiro para o grafo.
 */
void criarArestas(Grafo* g) {
    for (int i = 0; i < g->numVertices; i++) {
        for (int j = 0; j < g->numVertices; j++) {
            if (i != j && g->vertices[i].frequencia == g->vertices[j].frequencia) {
                Aresta* nova = malloc(sizeof(Aresta));
                nova->destino = &g->vertices[j];
                nova->prox = g->vertices[i].adj;
                g->vertices[i].adj = nova;
            }
        }
    }
}

/**
 * @brief Realiza uma procura em profundidade (DFS) no grafo.
 * @param v Vértice de partida.
 */
void dfs(Vertice* v) {
    if (v == NULL || v->visitado) return;

    v->visitado = 1;
    printf("(%d, %d) [%c]\n", v->x, v->y, v->frequencia);

    Aresta* a = v->adj;
    while (a != NULL) {
        dfs(a->destino);
        a = a->prox;
    }
}

/**
 * @brief Reinicia o estado de todos os vértices para não visitado.
 * @param g Ponteiro para o grafo.
 */
void resetarVisitados(Grafo* g) {
    for (int i = 0; i < g->numVertices; i++) {
        g->vertices[i].visitado = 0;
    }
}

/**
 * @brief Realiza uma procura em largura (BFS) no grafo.
 * @param inicio Vértice de partida.
 */
void bfs(Vertice* inicio) {
    if (inicio == NULL) return;

    Vertice* fila[1000];
    int frente = 0, tras = 0;

    fila[tras++] = inicio;

    while (frente < tras) {
        Vertice* atual = fila[frente++];

        if (atual->visitado) continue;

        atual->visitado = 1;
        printf("(%d, %d) [%c]\n", atual->x, atual->y, atual->frequencia);

        for (Aresta* a = atual->adj; a != NULL; a = a->prox) {
            if (!a->destino->visitado) {
                fila[tras++] = a->destino;
            }
        }
    }
}

/**
 * @brief Lista todos os caminhos possíveis entre dois vértices.
 *
 * @param origem Vértice de origem.
 * @param destino Vértice de destino.
 * @param trajeto Array de strings com coordenadas do caminho.
 * @param nivel Nível atual de profundidade (índice do trajeto).
 */
void caminhos(Vertice* origem, Vertice* destino, char trajeto[100][20], int nivel) {
    if (origem == NULL || origem->visitado) return;

    origem->visitado = 1;
    sprintf(trajeto[nivel], "(%d,%d)", origem->x, origem->y);

    if (origem == destino) {
        for (int i = 0; i <= nivel; i++) {
            printf("%s", trajeto[i]);
            if (i < nivel) printf(" -> ");
        }
        printf(" -> FIM\n");
        origem->visitado = 0;
        return;
    }

    for (Aresta* a = origem->adj; a != NULL; a = a->prox) {
        caminhos(a->destino, destino, trajeto, nivel + 1);
    }

    origem->visitado = 0;
}

/**
 * @brief Lista interseções entre antenas de frequências diferentes que ocupam a mesma posição.
 *
 * @param g Ponteiro para o grafo.
 * @param f1 Frequência 1.
 * @param f2 Frequência 2.
 */
void intersecoes(Grafo* g, char f1, char f2) {
    for (int i = 0; i < g->numVertices; i++) {
        Vertice* v1 = &g->vertices[i];
        if (v1->frequencia != f1) continue;

        for (int j = 0; j < g->numVertices; j++) {
            Vertice* v2 = &g->vertices[j];
            if (v2->frequencia != f2) continue;

            if (v1->x == v2->x && v1->y == v2->y) {
                printf("Interseção em (%d,%d) entre frequências %c e %c\n",
                    v1->x, v1->y, f1, f2);
            }
        }
    }
}