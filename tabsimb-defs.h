#ifndef TABSIMB_DEFINICOES_H
#define TABSIMB_DEFINICOES_H

#include "lista.h"
#include <stdbool.h>

/* ================================================================= */
/* INFORMACOES BASICAS DO ARQUIVO */
/* ================================================================= */

/* DESCRICAO: contem as definicoes de tipos de dados uteis para o
   desenvolvimento do compilador, como, por exemplo, o que e uma
   tabela de simbolos, o que e uma entrada da tabela de simbolos,
   etc. */
/* CRIADO EM: 07 mar. 2021. */

/* ================================================================= */
/* DEFINICOES DE TIPOS DE DADOS UTEIS PARA O COMPILADOR */
/* ================================================================= */

/* ----------------------------------------------------------------- */
/* DADOS DOS TIPOS DE DADOS DA LINGUAGEM  (bool, char, ...) */
/* ----------------------------------------------------------------- */

typedef struct dados_de_tipo_t
{
    char *nome;   /* Nome do tipo. */
    size_t bytes; /* Quantidade de bytes ocupados por
								 * um valor deste tipo. */
} tipo_t;

/* ----------------------------------------------------------------- */
/* ENTRADA DE UMA TABELA DE SIMBOLOS */
/* ----------------------------------------------------------------- */

/* A definicao de uma variavel ou de uma funcao e a instrucao que 
 * provoca a alocacao da variavel ou da funcao na memoria. Toda definicao 
 * tambem e uma declaracao. Uma declaracao de variavel ou de funcao 
 * simplesmente anuncia as propriedades da variavel ou da funcao, sem, 
 * contudo, causar a alocacao. Em C, por exemplo, declaracoes de funcoes
 * sao os prototipos que geralmente aparecem em arquivos .h ou no topo 
 * de arquivos .c. Ja definicoes de funcao sao acompanhadas pelo codigo
 * que devem executar, normalmente em arquivos .c. Declaracoes de
 * variaveis, em C, sao acompanhadas da palavra-chave "extern".
 * No caso da linguagem do compilador que construimos,
 * nao ha como declarar uma variavel sem defini-la, enquanto uma funcao
 * pode ser primeiro declarada e depois definida. */

typedef struct entrada_de_tabela_t
{
    char *id;        /* Identificador. E a "chave primaria"
								 * da entrada. */
    int tipo_entr;   /* Tipo da entrada (funcao, variavel ou
								 * ainda nao especificado). */
    tipo_t *tipo;    /* Tipo de dados da variavel ou da
								   funcao (bool, int, etc). */
    void *valor;     /* Valor da variavel ou valor de
								   retorno da funcao. */
    lista_t *params; /* Tipos dos parametros da funcao */
    bool definida;   /* Flag que indica se existe definicao
								   para a entrada. */
    bool declarada;  /* Flag que indica se existe uma
								   declaracao para a entrada. */
    int linha;       /* Linha em que a variavel ou a funcao
								   foi definida. */
    int coluna;      /* Coluna em que a variavel ou a funcao
								   foi definida. */
} entr_t;

/* ----------------------------------------------------------------- */
/* TABELA DE SIMBOLOS. */
/* ----------------------------------------------------------------- */

/* Nesse compilador, uma tabela de simbolos e simplesmente uma lista
 * encadeada de entradas. */

typedef struct tabela_de_simbolos_t
{
    lista_t *entrs; /* Lista que armazena os dados da 
							 * tabela. */
} tabsimb_t;

/* ================================================================= */

#endif
