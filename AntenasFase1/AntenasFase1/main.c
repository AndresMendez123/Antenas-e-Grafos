#include <stdio.h>
#include "estruturas.h"


#pragma warning (disable:4996))

int main() {
    ANTENA* lista = NULL;
    LOCAL* locais = NULL;
    int linhas, colunas;

    lista = lerMatrizDeFicheiro("mapa.txt", &linhas, &colunas);
    if (!lista) {
        printf("Erro ao carregar as antenas.\n");
        return 1;
    }

    locais = deduzirEfeitosNefastos(lista);

    printf("\n--- Lista de Antenas ---\n");
    listarAntenas(lista);

    printf("\n--- Localizações com Efeito Nefasto ---\n");
    listarLocalizacoes(locais);

    printf("\n--- Mapa da Cidade ---\n");
    desenharMatriz(linhas, colunas, lista, locais);


    return 0;
}