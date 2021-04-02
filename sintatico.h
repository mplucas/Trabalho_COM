# include "bytecode.h"
# include <stdio.h>
# include <string.h>
# include "tabsimb.h"
# include "tabsimb-defs.h"
# include "trabalho.tab.h"

/* ================================================================= */
/* INFORMACOES BASICAS DO ARQUIVO. */
/* ================================================================= */

/* DESCRICAO: contem as declaracoes basicas do analisador sintatico. */
/* CRIADO EM: 24 mar. 2021. */

/* ================================================================= */
/* VARIAVEIS GLOBAIS. */
/* ================================================================= */

/* Variaveis globais do Flex e do Bison. */
extern FILE *yyin;		/* Especifica o fluxo de entrada do compilador. */
extern char *yytext;	
extern YYSTYPE yylval;

/* Variaveis globais do analisador lexico. */
extern int linha;
extern int coluna;

/* Variaveis globais definidas em outros arquivos. */
extern tabsimb_t *tab;	/* Tabela de simbolos. */

/* Variaveis globais do analisador sintatico. */

/* As quatro variaveis servem para passar o valor de uma constante
 * recem reconhecida no analisador lexico para o sintatico. */
bool cte_bool;			/* Um valor booleano. E */
char cte_char;			/* Um caractere. */
float cte_float;		/* Um numero de ponto flutuante. */
int cte_int;			/* Um numero inteiro. */

char *id_func_chamada;	/* Identificador da ultima funcao chamada. */

lista_t *inics;			/* Armazena os identificadores de uma lista de 
						/* definicao de variaveis (int a, b, c;). */
lista_t *args;			/* Armazena os tipos dos argumentos de uma
						/* chamada de funcao. */

/* ================================================================= */
/* ASSINATURAS DE FUNCOES. */
/* ================================================================= */

/* Funcoes do Flex e do Bison. */
extern int yylex (void);		/* Invoca o analisador lexico. */
extern int yyparse (void);		/* Invoca o analisador sintatico. */
void yyerror (const char* mensagem);	/* Rotina padrao de erros. */

/* Funcoes do analisador sintatico. */
/* Essas funcoes executam as acoes semanticas associadas as regras de
 * producao quanto tais acoes sao relativamente extensas. O nome da
 * funcao e o nome do nao-terminal que encabeca a regra de producao. */

tipo_t *chamada_funcao (char *id);
void comp_inicializar (void);
bool decl_var (tipo_t *tipo_def);
tipo_t *expr_atrib (char *id, tipo_t *tipo_val);
tipo_t *expr_e (tipo_t *tipo1, tipo_t *tipo2);
tipo_t *expr_igual (int oper, tipo_t *tipo1, tipo_t *tipo2);
tipo_t *expr_mult (int oper, tipo_t *expr1, tipo_t *expr2);
tipo_t *expr_ou (tipo_t *tipo1, tipo_t *tipo2);
tipo_t *expr_ou_excl (tipo_t *tipo1, tipo_t *tipo2);
tipo_t *expr_relac (int oper, tipo_t *tipo1, tipo_t *tipo2);
tipo_t *expr_simpl_r5 (char *id);
tipo_t *expr_soma (int oper, tipo_t *expr1, tipo_t *expr2);
tipo_t *expr_unaria (int oper, tipo_t *expr);
bool inic (char *id, tipo_t *tipo);
lista_t *lista_arg (tipo_t *tipo);
bool lista_inic (char *id);
void raiz (bool imprimir_tabela);

