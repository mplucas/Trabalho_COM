# include "lexico.h"
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include "tabsimb-defs.h"
# include "tabsimb.h"
# include "trabalho.tab.h"

/* ================================================================= */
/* INFORMACOES BASICAS DO ARQUIVO. */
/* ================================================================= */

/* DESCRICAO: contem as funcoes utilizadas pelo analisador lexico. */
/* CRIADO EM: 24 mar. 2021. */

/* ================================================================= */
/* FUNCOES DO ANALISADOR LEXICO. */
/* ================================================================= */

/* ------------------------------------------------------------ */
/* EXECUTAR A ACAO LEXICO CORRESPONDENTE AO TOKEN RECONHECIDO. */
/* ------------------------------------------------------------ */

int acao_lexica (int token)
{	
	switch (token) 
	{
		/* Constantes disponibilizam seus tipos para o analisador
		 * sintatico. yylval e uma struct definida no Bison que 
		 * permite a atribuicao de valores a tokens (no analisador 
		 * lexico) e a nao-terminais (no analisador sintatico). Por 
		 * meio da adicao do cabecalho *.tab.h ela se torna disponivel 
		 * no Flex. Os campos dessa struct sao definidos na declaracao 
		 * %union, do Bison. */
		 
		case T_BOOL: 	
			cte_bool = (strcmp ("false", yytext) == 0 ? false : true); 
			yylval.tipo = tipo_obter ("bool"); 	
			break;
		
		case T_CHAR:	
			cte_char = yytext[1];
			yylval.tipo = tipo_obter ("char"); 	
			break;
		
		case T_FLOAT:	
			cte_float = atof (yytext);
			yylval.tipo = tipo_obter ("float");
			break;
		
		case T_INT:		
			cte_int = atoi (yytext); 
			yylval.tipo = tipo_obter ("int"); 
			break;
		
		/* Nomes de tipo disponibilizam seus tipos paar o analisador
		 * sintatico. */
		case T_TIPO:	
			yylval.tipo = tipo_obter (yytext); 	
			break;			
		
		/* Identificadores sao inseridos na tabela de simbolos junto com
		 * suas informacoes de linha e coluna. Eles tambem sao 
		 * disponibilizados ao analisador sintatico. */
		case T_ID:
			if (tab_criar_entr (yytext) == true) {
				tab_atrib_linha (yytext, linha);
				tab_atrib_coluna (yytext, coluna);
			}
			char *id = malloc (yyleng + 1);
			strcpy (id, yytext);
			yylval.id = id;
			break;
		
		/* Erros exibem mensagens informativas. */
		case T_ERRO: /* Erro lexico. */
			yyerror ("token desconhecido.\n");
			break;
	}
	
	/* Atualizacao da linha e da coluna onde o cursor esta de acordo
		com o token reconhecido. */
	atualizar_cursor();
	
	return (token);
}

/* ------------------------------------------------------------ */
/* ATUALIZAR POSICAO (LINHA E COLUNA) DO CURSOR. */
/* ------------------------------------------------------------ */

void atualizar_cursor (void) 
{	
	if (strcmp (yytext, "\n") == 0) {
		linha++;
		coluna = 1;
		return;
	}
	coluna += yyleng;
}
