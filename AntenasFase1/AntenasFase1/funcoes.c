/*!
 * @file funcoes.c
 * @author Andrés Mendez 
 * @date 2025-05-16
 * @brief Implementa��o das fun��es da Fase 1.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "estruturas.h"

#pragma warning (disable:4996)

 /**
  * @brief Cria uma nova antena com os dados fornecidos.
  * @param freq Frequencia da antena.
  * @param linha Linha da matriz onde se encontra.
  * @param coluna Coluna da matriz onde se encontra.
  * @return Ponteiro para a nova antena criada.
  */
ANTENA* criarAntena(char freq, int linha, int coluna) {
    ANTENA* nova = (ANTENA*)malloc(sizeof(ANTENA));
    if (!nova) return NULL;
    nova->freq = freq;
    nova->linha = linha;
    nova->coluna = coluna;
    nova->prox = NULL;
    return nova;
}

/**
 * @brief Insere uma antena na lista de forma ordenada e evita duplicados.
 * @param lista Lista atual de antenas.
 * @param freq Frequencia da nova antena.
 * @param linha Linha onde esta a antena.
 * @param coluna Coluna onde esta a antena.
 * @return Nova cabeca da lista.
 */
ANTENA* inserirOrdenadoAntena(ANTENA* lista, char freq, int linha, int coluna) {
    ANTENA* nova = criarAntena(freq, linha, coluna);
    if (!nova) return lista;

    for (ANTENA* p = lista; p != NULL; p = p->prox) {
        if (p->linha == linha && p->coluna == coluna) {
            free(nova);
            return lista;
        }
    }

    if (!lista || freq < lista->freq ||
        (freq == lista->freq && linha < lista->linha) ||
        (freq == lista->freq && linha == lista->linha && coluna < lista->coluna)) {
        nova->prox = lista;
        return nova;
    }

    ANTENA* aux = lista;
    while (aux->prox &&
        (aux->prox->freq < freq ||
            (aux->prox->freq == freq && aux->prox->linha < linha) ||
            (aux->prox->freq == freq && aux->prox->linha == linha && aux->prox->coluna < coluna))) {
        aux = aux->prox;
    }

    nova->prox = aux->prox;
    aux->prox = nova;

    return lista;
}

/**
 * @brief Remove uma antena com as coordenadas indicadas.
 * @param lista Lista de antenas.
 * @param linha Linha da antena a remover.
 * @param coluna Coluna da antena a remover.
 * @return Nova cabeca da lista.
 */
ANTENA* removerAntena(ANTENA* lista, int linha, int coluna) {
    if (!lista) return NULL;

    if (lista->linha == linha && lista->coluna == coluna) {
        ANTENA* temp = lista;
        lista = lista->prox;
        free(temp);
        return lista;
    }

    ANTENA* atual = lista;
    while (atual->prox) {
        if (atual->prox->linha == linha && atual->prox->coluna == coluna) {
            ANTENA* temp = atual->prox;
            atual->prox = temp->prox;
            free(temp);
            break;
        }
        atual = atual->prox;
    }
    return lista;
}

/**
 * @brief Cria uma nova localizacao com efeito nefasto.
 * @param linha Linha da localizacao.
 * @param coluna Coluna da localizacao.
 * @return Ponteiro para o novo local.
 */
LOCAL* criarLocal(int linha, int coluna) {
    LOCAL* nova = (LOCAL*)malloc(sizeof(LOCAL));
    if (!nova) return NULL;
    nova->linha = linha;
    nova->coluna = coluna;
    nova->prox = NULL;
    return nova;
}

/**
 * @brief Insere uma localizacao afetada, evitando duplicados.
 * @param lista Lista de locais.
 * @param linha Linha a inserir.
 * @param coluna Coluna a inserir.
 * @return Nova cabeca da lista.
 */
LOCAL* inserirLocal(LOCAL* lista, int linha, int coluna) {
    for (LOCAL* p = lista; p != NULL; p = p->prox) {
        if (p->linha == linha && p->coluna == coluna)
            return lista;
    }
    LOCAL* nova = (LOCAL*)malloc(sizeof(LOCAL));
    nova->linha = linha;
    nova->coluna = coluna;
    nova->prox = lista;
    return nova;
}

/**
 * @brief Lista todas as antenas na consola.
 * @param lista Lista de antenas.
 * @return 1 se listado com sucesso, 0 se lista vazia.
 */
int listarAntenas(ANTENA* lista) {
    if (!lista) return 0;
    printf("Frequ�ncia\tLinha\tColuna\n");
    printf("-----------------------------\n");
    while (lista) {
        printf("%c\t\t%d\t%d\n", lista->freq, lista->linha, lista->coluna);
        lista = lista->prox;
    }
    return 1;
}

/**
 * @brief Lista todas as localizacoes com efeito nefasto.
 * @param lista Lista de locais.
 * @return 1 se listado com sucesso, 0 se lista vazia.
 */
int listarLocalizacoes(LOCAL* lista) {
    if (!lista) return 0;
    printf("Linha\tColuna\n");
    printf("----------------\n");
    while (lista) {
        printf("%d\t%d\n", lista->linha, lista->coluna);
        lista = lista->prox;
    }
    return 1;
}

/**
 * @brief Desenha a matriz com antenas e locais nefastos.
 * @param linhas Numero de linhas da matriz.
 * @param colunas Numero de colunas da matriz.
 * @param lista Lista de antenas.
 * @param locais Lista de locais afetados.
 * @return 1 se desenhado, 0 se listas vazias.
 */
int desenharMatriz(int linhas, int colunas, ANTENA* lista, LOCAL* locais) {
    if (!lista && !locais) return 0;
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            int impresso = 0;
            for (ANTENA* a = lista; a != NULL; a = a->prox) {
                if (a->linha == i && a->coluna == j) {
                    printf("%c", a->freq);
                    impresso = 1;
                    break;
                }
            }
            if (!impresso) {
                for (LOCAL* l = locais; l != NULL; l = l->prox) {
                    if (l->linha == i && l->coluna == j) {
                        printf("#");
                        impresso = 1;
                        break;
                    }
                }
            }
            if (!impresso) printf(".");
        }
        printf("\n");
    }
    return 1;
}

/**
 * @brief Le uma matriz do ficheiro e cria a lista ligada de antenas.
 * @param nomeFicheiro Nome do ficheiro de entrada.
 * @param linhas Ponteiro para armazenar o numero de linhas.
 * @param colunas Ponteiro para armazenar o numero de colunas.
 * @return Lista ligada de antenas.
 */
ANTENA* lerMatrizDeFicheiro(const char* nomeFicheiro, int* linhas, int* colunas) {
    FILE* f = fopen(nomeFicheiro, "r");
    if (!f) {
        printf("Erro ao abrir ficheiro %s.\n", nomeFicheiro);
        return NULL;
    }

    ANTENA* lista = NULL;
    char buffer[1024];
    *linhas = 0;
    *colunas = 0;

    while (fgets(buffer, sizeof(buffer), f)) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') buffer[len - 1] = '\0';

        int j = 0;
        while (buffer[j] != '\0') {
            if (buffer[j] != '.') {
                lista = inserirOrdenadoAntena(lista, buffer[j], *linhas, j);
            }
            j++;
        }
        if (*linhas == 0) *colunas = j;
        (*linhas)++;
    }

    fclose(f);
    return lista;
}

/**
 * @brief Deduz as localizacoes com efeito nefasto com base em pares de antenas.
 * @param antenas Lista de antenas.
 * @return Lista de locais com efeito nefasto.
 */
LOCAL* deduzirEfeitosNefastos(ANTENA* antenas) {
    LOCAL* nefastas = NULL;

    for (ANTENA* a1 = antenas; a1; a1 = a1->prox) {
        for (ANTENA* a2 = a1->prox; a2; a2 = a2->prox) {
            if (a1->freq == a2->freq) {
                int dlin = a2->linha - a1->linha;
                int dcol = a2->coluna - a1->coluna;

                if ((dcol == 0) || (abs(dlin) == abs(dcol)) ||
                    abs(dlin) == 2 * abs(dcol) || abs(dcol) == 2 * abs(dlin)) {

                    nefastas = inserirLocal(nefastas, a1->linha - dlin, a1->coluna - dcol);
                    nefastas = inserirLocal(nefastas, a2->linha + dlin, a2->coluna + dcol);
                }
            }
        }
    }
    return nefastas;
}

