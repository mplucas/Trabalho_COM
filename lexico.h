# include "lista.h"
# include <stdio.h>
# include "tabsimb-defs.h"

/* ================================================================= */
/* INFORMACOES BASICAS DO ARQUIVO */
/* ================================================================= */

/* DESCRICAO: contem as inclusoes necessarias para que o arquivo
	relativo ao analisador lexico funcione. */
/* CRIADO EM: 23 mar. 2021. */

/* ================================================================= */
/* VARIAVEIS GLOBAIS. */
/* ================================================================= */

extern int yyleng;		/* Quantidade de caracteres do ultimo token 
						 * reconhecido. */
extern char* yytext;	/* Ultimo token reconhecido. */

int linha;				/* Linha do ultimo token reconhecido. */
int coluna;				/* Coluna do ultimo token reconhecido. */

extern tabsimb_t *tab;	/* Tabela de simbolos (definida no arquivo
						 * tabsimb.c). */

/* ================================================================= */
/* DECLARACOES DE FUNCOES. */
/* ================================================================= */

int acao_lexica (int token);
void atualizar_cursor (void);

extern void yyerror (const char* mensagem);

