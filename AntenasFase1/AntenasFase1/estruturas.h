/*!
 * @file estruturas.h
 * @author Andrés Mendez 
 * @date 2025-05-16
 * @brief Estruturas de dados para Fase 1 - Antenas com Lista Ligada.
 */

#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

 /**
  * @struct antena
  * @brief Representa uma antena com frequencia, posicao na matriz e ponteiro para a proxima.
  */
typedef struct antena {
    char freq;                /**< Frequencia da antena */
    int linha;                /**< Linha na matriz */
    int coluna;               /**< Coluna na matriz */
    struct antena* prox;      /**< Ponteiro para a proxima antena na lista */
} ANTENA;

/**
 * @struct localizacao
 * @brief Representa uma localizacao com efeito nefasto.
 */
typedef struct localizacao {
    int linha;                 /**< Linha da localizacao */
    int coluna;                /**< Coluna da localizacao */
    struct localizacao* prox; /**< Ponteiro para a proxima localizacao na lista */
} LOCAL;

// Funcoes para antenas
ANTENA* criarAntena(char freq, int linha, int coluna);
ANTENA* inserirOrdenadoAntena(ANTENA* lista, char freq, int linha, int coluna);
ANTENA* removerAntena(ANTENA* lista, int linha, int coluna);
int listarAntenas(ANTENA* lista);

// Funcoes para localizacoes
LOCAL* criarLocal(int linha, int coluna);
LOCAL* inserirLocal(LOCAL* lista, int linha, int coluna);
int listarLocalizacoes(LOCAL* lista);

// Operacoes gerais
ANTENA* lerMatrizDeFicheiro(const char* nomeFicheiro, int* linhas, int* colunas);
LOCAL* deduzirEfeitosNefastos(ANTENA* lista);
int desenharMatriz(int linhas, int colunas, ANTENA* lista, LOCAL* locais);

#endif