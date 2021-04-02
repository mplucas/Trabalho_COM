# ifndef LISTA_DEFINICOES_H
# define LISTA_DEFINICOES_H

# include <stdlib.h>

/* ================================================================= */
/* INFORMACOES BASICAS DO ARQUIVO. */
/* ================================================================= */

/* DESCRICAO: comtem as definicoes do tipo de dados que implementa
 * uma lista simplesmente encadeada. */

/* ================================================================= */
/* DEFINICOES DE TIPOS DE DADOS. */
/* ================================================================= */

/* ----------------------------------------------------------------- */
/* NO DA LISTA. */
/* ----------------------------------------------------------------- */

struct lista_no_t {
	struct lista_no_t *prox;		/* Proximo do da lista. */
	void *dado;						/* Endereco do dado. */
};
typedef struct lista_no_t no_t;

/* ----------------------------------------------------------------- */
/* CABECALHO DA LISTA. */
/* ----------------------------------------------------------------- */

struct lista_cabecalho_t {
	size_t tam_unit;				/* Tamanho em bytes de uma unidade
									 * de dados. */
	size_t tamanho;					/* Quantidade de dados armazenados
									 * na lista. */
	no_t *inicial;					/* No inicial da lista. */
};
typedef struct lista_cabecalho_t lista_t;

/* ================================================================= */

# endif
