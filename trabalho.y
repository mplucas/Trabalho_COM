/* ================================================================= */
/* DECLARACOES E DEFINICOES BASICAS */
/* ================================================================= */

/* ----------------------------------------------------------------- */
/* INCLUDES NECESSARIOS */
/* ---------------------------------------------------------------- */

%{
# include "sintatico.h"
%}

/* ----------------------------------------------------------------- */
/* TIPOS DE DADOS RETORNADOS PELOS TOKENS E PELOS NAO-TERMINAIS */
/* ----------------------------------------------------------------- */

%union {
	tipo_t *tipo;		/* Um tipo de dados. */
	char *id;			/* Identificador. */
	int token;			/* O codigo de um token no anal. lexico. */
}

/* ----------------------------------------------------------------- */
/* LISTA DE TOKENS */
/* ----------------------------------------------------------------- */

/* O token ELSE_FALSO nunca e usado, porem ele serve para resolver o 
	conflito SR if/if/else. Ele precisa aparecer antes do token 
	T_ELSE, portanto e o unico que esta fora da ordem alfabetica. */

/* O valor entre < e > especifica qual campo de yylval (veja o %union)
 * acima deve ser usado quando se desejar associar um valor ao token ou
 * ao nao-terminal. */

%token T_ACOLCH
%token T_APAREN
%token T_ATRIB
%token T_ASPAS_SIMPL
%token T_BRANCO
%token T_BREAK
%token <tipo> T_BOOL
%token <tipo> T_CHAR
%token <tipo> T_FLOAT
%token <tipo> T_INT
%token T_CONTINUE
%token <token> T_DIFER
%token <token> T_DIV
%token T_DO
%token <token> T_E
%nonassoc T_ELSE_FALSO
%nonassoc T_ELSE
%token T_ERRO
%token T_FCOLCH
%token T_FOR
%token T_FPAREN
%token <id> T_ID
%token T_IF
%token <token> T_IGUAL
%token <token> T_MAIOR
%token <token> T_MAIOR_IGUAL
%token <token> T_MAIS
%token <token> T_MENOR
%token <token> T_MENOR_IGUAL
%token <token> T_MENOS
%token <token> T_NAO
%token T_NEWLINE
%token <token> T_OU
%token <token> T_OU_EXCL
%token T_PEV
%token <token> T_RESTO
%token T_RETURN
%token <tipo> T_TIPO
%token <token> T_VEZES
%token T_VIRG
%token T_VOID
%token T_WHILE

%type <id>		inic
%type <tipo> 	chamada_funcao	expr 			expr_atrib
%type <tipo> 	expr_e			expr_igual		expr_mult
%type <tipo> 	expr_ou			expr_ou_excl 	expr_relac
%type <tipo> 	expr_simpl		expr_soma 		expr_unaria
%type <token>	oper_unario		oper_unario_log

/* ----------------------------------------------------------------- */
/* DEFINICAO DA RAIZ DA GRAMATICA. */
/* ----------------------------------------------------------------- */

%start raiz

%%

/* ================================================================= */
/* GRAMATICA. */
/* ================================================================= */

/* O conteudo entre chaves apos as regras de producao indicam as acoes
 * que devem ser executados apos a regra ser reconhecido. E ai que se
 * executam as acoes de analise semantica. Essas chaves tambem poderiam 
 * aparecer no meio do corpo (lado direito) da regra de producao. Nesse 
 * caso, elas indicariam as acoes a serem executados quando o
 * reconhecimento da regra de producao atingiu o ponto onde as chaves
 * se encontram. */
 
 /* As acoes semanticas associadas sao apresentadas nas funcoes do 
  * arquivo sintatico.c. */

raiz			
	:	unid_traducao {
			raiz (false);
		}
	;

unid_traducao	
	:	unid_traducao decl_externa
	|	decl_externa
	;

decl_externa	
	:	instr_decl
	|	def_funcao
	;				

def_funcao		
	:	decl_funcao cmd_composto
	;

lista_param		
	:	param
	|	lista_param T_VIRG param
	;

param			
	:	T_TIPO T_ID
	;

instrucao
	:	instr_decl
	|	cmd_composto
	|	cmd_selecao
	|	cmd_repeticao
	|	cmd_desvio
	|	cmd_expr
	;

instr_decl		
	:	decl T_PEV
	;
				
decl			
	:	decl_var 
	|	decl_funcao 
	;

decl_var		
	:	T_TIPO lista_inic {
			puts ("declvar1");
			decl_var ($1);
		}
 	;				

lista_inic
	: 	lista_inic T_VIRG inic {
			puts ("lista_inic1");
			lista_inic ($3);
		}
	| 	inic {
			puts ("lista_inic2");
			lista_inic ($1); 
		}
	;

inic
	: 	T_ID {
			puts ("inic1");
			inic ($1, NULL);
		}	
	|	T_ID T_ATRIB expr {
			puts ("inic2");
			inic ($1, $3);
		}
	;

decl_funcao		
	: 	T_TIPO T_ID T_APAREN lista_param T_FPAREN 	
	| 	T_VOID T_ID T_APAREN lista_param T_FPAREN	
	| 	T_TIPO T_ID T_APAREN T_VOID T_FPAREN		
	| 	T_VOID T_ID T_APAREN T_VOID T_FPAREN
	;		

cmd_composto	
	: 	T_ACOLCH lista_instr T_FCOLCH
	| 	T_ACOLCH T_FCOLCH
	;

lista_instr		
	:	lista_instr instrucao
	|	instrucao
	;				

cmd_selecao		
	:	T_IF T_APAREN expr T_FPAREN instrucao %prec T_ELSE_FALSO
	|	T_IF T_APAREN expr T_FPAREN instrucao T_ELSE instrucao
	;

cmd_repeticao	
	:	cmd_for | cmd_while | cmd_do_while 
	;

cmd_for			
	:	T_FOR T_APAREN expr T_PEV expr 	T_PEV expr 	T_FPAREN cmd_composto
	|	T_FOR T_APAREN expr T_PEV expr 	T_PEV 		T_FPAREN cmd_composto
	|	T_FOR T_APAREN expr T_PEV 		T_PEV expr 	T_FPAREN cmd_composto
	|	T_FOR T_APAREN expr T_PEV		T_PEV  		T_FPAREN cmd_composto
	|	T_FOR T_APAREN 		T_PEV expr 	T_PEV expr 	T_FPAREN cmd_composto
	|	T_FOR T_APAREN 		T_PEV expr 	T_PEV 		T_FPAREN cmd_composto
	|	T_FOR T_APAREN 		T_PEV 		T_PEV expr 	T_FPAREN cmd_composto
	|	T_FOR T_APAREN 		T_PEV  		T_PEV  		T_FPAREN cmd_composto
	;

cmd_while		
	:	T_WHILE T_APAREN expr T_FPAREN cmd_composto
	;

cmd_do_while	
	:	T_DO cmd_composto T_WHILE T_APAREN expr T_FPAREN T_PEV
	;

cmd_desvio		
	:	desvio T_PEV
	;

desvio
	:	T_BREAK 
	|	T_CONTINUE 
	|	retorno {
            bytecodeReturn();
        }
	;

retorno			
	:	T_RETURN 
	|	T_RETURN expr
	;

cmd_expr
	:	expr T_PEV
	;

expr
	:	expr_atrib
	;

expr_atrib
	:	T_ID T_ATRIB expr_atrib	{
			
			puts ("expr_atrib1");
			$$ = expr_atrib ($1, $3);
		}
	|	expr_ou
	;

expr_ou	
	:	expr_ou T_OU expr_e	{
			puts ("expr_ou");
			$$ = expr_ou ($1, $3); 
		}
	|	expr_e
	;

expr_e		
	:	expr_e T_E expr_ou_excl	{
			puts ("expr_e");
			$$ = expr_e ($1, $3); 
		}
	|	expr_ou_excl
	;			

expr_ou_excl	
	:	expr_ou_excl T_OU_EXCL expr_igual {
			puts ("expr_ou_excl");
			$$ = expr_ou_excl ($1, $3); 
		}
	|	expr_igual
	;

expr_igual		
	:	expr_igual T_IGUAL expr_relac
	|	expr_igual T_DIFER expr_relac
	|	expr_relac
	; 

expr_relac
	:	expr_relac T_MENOR expr_soma {
			puts ("expr_relac1");
			$$ = expr_relac ($2, $1, $3); 
		}
	|	expr_relac T_MAIOR expr_soma {
			puts ("expr_relac2");
			$$ = expr_relac ($2, $1, $3);
		}
	|	expr_relac T_MENOR_IGUAL expr_soma {
			puts ("expr_relac3");
			$$ = expr_relac ($2, $1, $3);
		}
	|	expr_relac T_MAIOR_IGUAL expr_soma {
			puts ("expr_relac4");
			$$ = expr_relac ($2, $1, $3); 
		}
	|	expr_soma
	;

expr_soma		
	:	expr_soma T_MAIS expr_mult {
			puts ("expr_soma1");
			$$ = expr_soma ($2, $1, $3); 
		}
	|	expr_soma T_MENOS expr_mult	{
			puts ("expr_soma2");
			$$ = expr_soma ($2, $1, $3); 
		}
	|	expr_mult						
	;

expr_mult		
	:	expr_mult T_VEZES expr_simpl {
			puts ("expr_mult1");
			$$ = expr_mult ($2, $1, $3);
		}
	|	expr_mult T_DIV expr_simpl {
			puts ("expr_mult2");
			$$ = expr_mult ($2, $1, $3);
		}
	|	expr_mult T_RESTO expr_simpl {
			puts ("expr_mult3");
			$$ = expr_mult ($2, $1, $3);
		}
	|	expr_unaria
	;

expr_unaria		
	:	oper_unario expr_simpl {
			puts ("expr_unaria1");
			$$ = expr_unaria ($1, $2);
		}
	|	expr_simpl
	;

expr_simpl
	:	T_APAREN expr T_FPAREN {
			puts ("expr_simpl1");
			$$ = $2;
		}
	|	T_BOOL {
			puts ("expr_simpl2");
			/* cte_bool */
			// $$ = yylval.tipo;
		}
	|	T_CHAR {
			puts ("expr_simpl3");
			/* cte_char */			
			// $$ = yylval.tipo;
		}
	|	T_FLOAT  {
			puts ("expr_simpl4");
			/* cte_float */
			// $$ = yylval.tipo; 
		}
	|	T_ID {
			puts ("expr_simpl5");
			$$ = expr_simpl_r5 ($1);
		}
	|	T_INT {
			puts ("expr_simpl6");
			/* cte_int */
			// $$ = yylval.tipo;
		}
	|	chamada_funcao {
            if (strcmp (id_func_chamada, "print_int") /* == 0?? */){
                printHeadStack();                
            }
        }
	;

chamada_funcao
	:	T_ID T_APAREN lista_arg T_FPAREN {
			puts ("chamada_funcao1");
			$$ = chamada_funcao ($1);
		} 
	|	T_ID T_APAREN T_FPAREN {
			puts ("chamada_funcao2");
			$$ = chamada_funcao ($1); 
		}
	;

lista_arg		
	:	lista_arg T_VIRG expr {
			puts ("lista_arg1");
			lista_arg ($3);
		}
	|	expr {
			puts ("lista_arg2");
			lista_arg ($1);
		}
	;

oper_unario		
	:	T_MAIS 
	|	T_MENOS 
	|	oper_unario_log ; 

oper_unario_log	
	:	T_NAO
	|	T_NAO oper_unario
	;

%%

/* ============================================================ */
/* FUNCOES DO ANALISADOR SINTATICO
/* ============================================================ */

/* Estao no arquivo sintatico.c. */


