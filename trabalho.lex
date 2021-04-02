/* ================================================================= */
/* DECLARACOES E DEFINICOES BASICAS */
/* ================================================================= */

%option noyywrap

%{
# include "lexico.h"
# include "trabalho.tab.h"
%}

DIGITO	[0-9]
LETRA	[_A-Za-z]

/* ================================================================= */
/* REGRAS DE TRADUCAO */
/* ================================================================= */

%%

[ \t\n]							{ acao_lexica (T_BRANCO); }
"="								{ return (acao_lexica (T_ATRIB)); }
"||"							{ return (acao_lexica (T_OU)); }
"&&"							{ return (acao_lexica (T_E)); }
"!"								{ return (acao_lexica (T_NAO)); }
"^"								{ return (acao_lexica (T_OU_EXCL)); }
"<"								{ return (acao_lexica (T_MENOR)); }
">"								{ return (acao_lexica (T_MAIOR)); }
"<="							{ return (acao_lexica (T_MENOR_IGUAL)); }
">="							{ return (acao_lexica (T_MAIOR_IGUAL)); }
"=="							{ return (acao_lexica (T_IGUAL)); }
"!="							{ return (acao_lexica (T_DIFER)); }
"+"								{ return (acao_lexica (T_MAIS)); }
"-"								{ return (acao_lexica (T_MENOS)); }
"*"								{ return (acao_lexica (T_VEZES)); }
"/"								{ return (acao_lexica (T_DIV)); }
"%"								{ return (acao_lexica (T_RESTO)); }
"("								{ return (acao_lexica (T_APAREN)); }
")"								{ return (acao_lexica (T_FPAREN)); }
"{"								{ return (acao_lexica (T_ACOLCH)); }
"}"								{ return (acao_lexica (T_FCOLCH)); }
";"								{ return (acao_lexica (T_PEV)); }
","								{ return (acao_lexica (T_VIRG)); }
"bool"|"char"|"float"|"int"		{ return (acao_lexica (T_TIPO)); }
"void"							{ return (acao_lexica (T_VOID)); }
"if"							{ return (acao_lexica (T_IF)); }
"else"							{ return (acao_lexica (T_ELSE)); }
"while"							{ return (acao_lexica (T_WHILE)); }
"for"							{ return (acao_lexica (T_FOR)); }
"do"							{ return (acao_lexica (T_DO)); }
"break"							{ return (acao_lexica (T_BREAK)); }
"continue"						{ return (acao_lexica (T_CONTINUE)); }
"return"						{ return (acao_lexica (T_RETURN)); }
"true"|"false"					{ return (acao_lexica (T_BOOL)); }
{DIGITO}+ 						{ return (acao_lexica (T_INT)); }
{DIGITO}+"."{DIGITO}+	 		{ return (acao_lexica (T_FLOAT)); }
'(.|\\n)'						{ return (acao_lexica (T_CHAR)); }
{LETRA}({LETRA}|{DIGITO})*		{ return (acao_lexica (T_ID)); }
. 								{ acao_lexica (T_ERRO); }

%%

/* ============================================================ */
/* FUNCOES DO ANALISADOR LEXICO
/* ============================================================ */

/* Estao no arquivo lexico.c. */

