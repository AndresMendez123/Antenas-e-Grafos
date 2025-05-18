
#include <stdio.h>
#include "estruturas.h"

int main() {
    Grafo g;
    carregarGrafo("mapa.txt", &g);
    criarArestas(&g);

    printf("\n--- DFS ---\n");
    dfs(&g.vertices[1]);

    resetarVisitados(&g);
    printf("\n--- BFS ---\n");
    bfs(&g.vertices[0]);

    resetarVisitados(&g);
    printf("\n--- Caminhos entre duas antenas ---\n");
    char trajeto[100][20];
    caminhos(&g.vertices[1], &g.vertices[4], trajeto, 0);

    printf("\n--- Interseções A e 0 ---\n");
    intersecoes(&g, 'A', 'B');

    return 0;
}
