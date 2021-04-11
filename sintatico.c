# include "sintatico.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "trabalho.tab.h"

/* ================================================================= */
/* INFORMACOES BASICAS DO ARQUIVO. */
/* ================================================================= */

/* DESCRICAO: contem as funcoes do analisador sintatico. */
/* CRIADO EM: 24 mar. 2021. */
												
/* ================================================================= */
/* FUNCOES DO ANALISADOR SINTATICO. */
/* ================================================================= */

/* ----------------------------------------------------------------- */
/* INICIALIZACAO DO COMPILADOR. */
/* ----------------------------------------------------------------- */

void comp_inicializar (void)
{   
    /* Inicializacao das variaveis globais. */
    linha = coluna = 1;
    inics = NULL;
    args = NULL;
    id_func_chamada = NULL;
    
    /* Criacao da tabela de simbolos. */
    tab_criar();

	/* Inicializacao da tabela de simbolos com as funcoes nativas da
		linguagem e a funcao main(). */
		
	char *id_print_int = "print_int";
	tab_criar_entr (id_print_int);
	tab_atrib_tipo_entr (id_print_int, ENTR_FUNC);
	tab_atrib_tipo (id_print_int, tipo_obter ("void"));
	tab_inserir_param (id_print_int, tipo_obter ("int")); 
	tab_definir (id_print_int);

    char *id_print_float = "print_float";
	tab_criar_entr (id_print_float);
	tab_atrib_tipo_entr (id_print_float, ENTR_FUNC);
	tab_atrib_tipo (id_print_float, tipo_obter ("void"));
	tab_inserir_param (id_print_float, tipo_obter ("float")); 
	tab_definir (id_print_float);

    char *id_print_char = "print_char";
	tab_criar_entr (id_print_char);
	tab_atrib_tipo_entr (id_print_char, ENTR_FUNC);
	tab_atrib_tipo (id_print_char, tipo_obter ("void"));
	tab_inserir_param (id_print_char, tipo_obter ("char")); 
	tab_definir (id_print_char);

    char *id_print_bool = "print_bool";
	tab_criar_entr (id_print_bool);
	tab_atrib_tipo_entr (id_print_bool, ENTR_FUNC);
	tab_atrib_tipo (id_print_bool, tipo_obter ("void"));
	tab_inserir_param (id_print_bool, tipo_obter ("bool")); 
	tab_definir (id_print_bool);
    
	
	char *id_scan_int = "scan_int";
	tab_criar_entr (id_scan_int);
	tab_atrib_tipo_entr (id_scan_int, ENTR_FUNC);
	tab_atrib_tipo (id_scan_int, tipo_obter ("int"));
	tab_definir (id_scan_int);
	
	char *id_rand = "rand";
	tab_criar_entr (id_rand);
	tab_atrib_tipo_entr (id_rand, ENTR_FUNC);
	tab_atrib_tipo (id_rand, tipo_obter ("int")); 
	tab_definir (id_rand);
	
	char *id_srand = "srand";
	tab_criar_entr (id_srand);
	tab_atrib_tipo_entr (id_srand, ENTR_FUNC);
	tab_atrib_tipo (id_srand, tipo_obter ("void"));
	tab_inserir_param (id_srand, tipo_obter ("int"));
	tab_definir (id_srand);
	
	char *id_time = "time";
	tab_criar_entr (id_time);
	tab_atrib_tipo_entr (id_time, ENTR_FUNC);
	tab_atrib_tipo (id_time, tipo_obter ("int"));
	tab_inserir_param (id_time, tipo_obter ("int"));
	tab_definir (id_time);
	
	char *id_main = "main";
	tab_criar_entr (id_main);
	tab_atrib_tipo_entr (id_main, ENTR_FUNC);
	tab_atrib_tipo (id_main, tipo_obter ("int"));
	tab_declarar (id_main);

    inicializarBytecodeFile();
}

/* ----------------------------------------------------------------- */
/* MAIN */
/* ----------------------------------------------------------------- */

int main (int argc, char **argv) 
{	
	/* Determinacao do fluxo de entrada. */
    yyin = ((argc == 2) ? fopen (argv[1], "r") : stdin);

	/* Inicializacao do compilador. */
	comp_inicializar();
	
	/* Execucao do analisador sintatico. */
    do {
        yyparse();
    } while (!(feof (yyin)));

    finalizarBytecodeFile();
    
    return (0);
}

/* ----------------------------------------------------------------- */
/* ROTINA DE ERROS */
/* ----------------------------------------------------------------- */

void yyerror (const char* mensagem)
{
    fprintf (stderr, "Erro @ (L%d, C%d): %s\n\n", 
    			linha, coluna, mensagem);
    // tab_imprimir();
    exit(1);
}

/* ================================================================= */
/* FUNCOES DE ACAO SEMANTICA (executadas quando uma regra gramatical
 * e parcialmente ou totalmente reconhecida). */
/* ================================================================= */

/* ----------------------------------------------------------------- */
/* chamada_funcao 	::= T_ID T_APAREN lista_arg T_FPAREN
					::= T_ID T_APAREN T_FPAREN */
/* ----------------------------------------------------------------- */

tipo_t *chamada_funcao (char *id)
{
	/* Identificando a ultima funcao chamada. */
	id_func_chamada = id;
	
	/* A lista de argumentos e, na verdade, uma lista de tipos, uma vez
	 * que os tipos e a quantidade dos argumentos e o que importa para 
	 * a analise semantica associada as chamadas de funcao. */
	
	/* Verificacao da definicao e do tipo do identificador. */
	if (tab_obter_declarada (id) == false) {
		yyerror ("funcao usada mas nao declarada.");
		return (NULL);
	}
	
	/* O identificador deve se referir a uma funcao. */
	if (tab_obter_tipo_entr (id) != ENTR_FUNC) {
		yyerror ("identificador nao se refere a uma funcao.");
		return (NULL);
	}
	
	/* Verificacao se as quantidades de argumentos e parametros sao 
	 * iguais. */
	
	size_t qtde_args = (args == NULL) ? 0 : lista_tamanho (args, NULL);
	if (tab_obter_qtde_params (id, NULL) != qtde_args) {
		yyerror ("a quantidade de argumentos na chamada da funcao nao"
					"coincide com a quantidade de parametros informados"
					"anteriormente.");
		return (NULL);
	}
	
	/* Comparacao entre os tipos dos argumentos e de seus respectivos
	 * parametros. */
	
	for (size_t i = 0; i < qtde_args; i++)
	{	
		/* Obtencao do argumento e seu respectivo parametro. */ 
		tipo_t *param = tab_obter_param (id, i);
		tipo_t *arg;
		lista_buscar (args, i, &arg);
		
		if (param == arg) {
			continue;
		}
	
		/* As regras de conversao de tipo na passagem de parametros sao
		 * as mesmas que governam a conversao de tipo realizada em
		 * atribuicoes. */
		if (tipo_obter_resultante (T_ATRIB, param, arg) == NULL) {
			yyerror ("tipo de argumento nao coincide com o do parametro.");
		}
	}
	lista_destruir (&args);
	return (tab_obter_tipo (id));
}

/* ----------------------------------------------------------------- */
/* decl_var	::= T_TIPO lista_inic */
/* ----------------------------------------------------------------- */

bool decl_var (tipo_t *tipo_def)
{
	/* Realizacao das verificacoes para cada identificador da lista. */
	
	for (size_t i = 0; i < lista_tamanho (inics, NULL); i++)
	{
		/* Obtencao do proximo identificador da lista. */
		char *id;
		lista_buscar (inics, i, &id);

		/* Se o identificador foi inicializado na sua definicao, entao
		 * o seu tipo na tabela de simbolos, inicialmente, e o tipo do
		 * valor com que ele foi inicializado. No entanto, o verdadeiro
		 * tipo do identificador e o declarado em sua definicao. */

		/* Obtencao do tipo de inicializacao do identificador. */
		tipo_t *tipo_inic = tab_obter_tipo (id);
		
		/* O identificador nao foi inicializado. Seu tipo, portanto, e o
		 * tipo especificado na sua definicao (tipo passado como 
		 * argumento. */
		if (tipo_inic == NULL) {
			tab_atrib_tipo (id, tipo_def);
			continue;
		}
		
		/* O identificador foi inicializado. O tipo especificado na sua
		 * definicao e o tipo do seu valor de inicializacao devem ser
		 * compativeis. */
		tipo_t *tipo_res;
		tipo_res = tipo_obter_resultante (T_ATRIB, tipo_def, tipo_inic);
		if (tipo_res == NULL) {
			yyerror ("operando de tipo incompativel.");
			return (false);
		}
		
		/* Correcao do tipo do identificador na tabela de simbolos. */ 
		if (tipo_inic != tipo_res) {
			tab_atrib_tipo (id, tipo_res);
		}
	}
	
	/* Apos a verificacao a lista de ids pode ser descartada. */
	lista_destruir (&inics);
	return (true);
}

/* ----------------------------------------------------------------- */
/* expr_atrib	::=	T_ID T_ATRIB expr_atrib
				::=	expr_ou */
/* ----------------------------------------------------------------- */

tipo_t *expr_atrib (char *id, tipo_t *tipo_val)
{
	/* Numa atribuicao, o lado esquerdo deve se referir a variavel 
	 * definida. */
	printf ("id = %s\n", id);
	
	int tipo_entr = tab_obter_tipo_entr (id);
	if ((tipo_entr != ENTR_VAR) && (tipo_entr != ENTR_VAZIA)) {
		yyerror ("o lado esquerdo da atribuicao nao se refere a "
					"variavel.");
		return (NULL);
	}
	
	if (tab_obter_definida (id) == false) {
		yyerror ("variavel usada mas nao definida.\n");
		return (NULL);
	}
	
	/* Verificacao da compatibilidade de tipos entre a variavel (lado
	 * esquerdo) e o valor atribuido (direito). */
	 
	tipo_t *tipo_id = tab_obter_tipo (id);
	tipo_t *tipo_res = tipo_obter_resultante (T_ATRIB, tipo_id, tipo_val);
	if (tipo_res == NULL) {
		yyerror ("o tipo do valor atribuido nao e compativel com o tipo"
					"da variavel.");
		return (NULL);
	}
}

/* ----------------------------------------------------------------- */
/* expr_e ::=	expr_e T_E expr_ou /*
/* ----------------------------------------------------------------- */

tipo_t *expr_e (tipo_t *tipo1, tipo_t *tipo2) 
{
	/* Obtencao do tipo de dados do resultado da operacao. */
	tipo_t *tipo_res = tipo_obter_resultante (T_E, tipo1, tipo2);
	if (tipo_res == NULL) {
		yyerror ("operandos de tipos incompativeis.");
		return (NULL);
	}
	return (tipo_res);		
}

/* ----------------------------------------------------------------- */
/* expr_igual	::= expr_igual T_IGUAL expr_relac
				::= expr_igual T_DIFER expr_relac */
/* ----------------------------------------------------------------- */

tipo_t *expr_igual (int oper, tipo_t *tipo1, tipo_t *tipo2)
{
	/* Obtencao do tipo de dados do resultado da operacao. */
	tipo_t *tipo_res = tipo_obter_resultante (oper, tipo1, tipo2);
	if (tipo_res == NULL) {
		yyerror ("operandos de tipos incompativeis.");
		return (NULL);
	}
	return (tipo_res);		
}

/* ----------------------------------------------------------------- */
/* expr_mult 	::= expr_mult T_VEZES expr_simpl
				::= expr_mult T_DIV expr_simpl
				::= expr_mult T_RESTO expr_simpl */
/* ----------------------------------------------------------------- */

tipo_t *expr_mult (int oper, tipo_t *tipo1, tipo_t *tipo2) 
{
	/* Obtencao do tipo de dados do resultado da operacao. */
	tipo_t *tipo_res = tipo_obter_resultante (oper, tipo1, tipo2);
	if (tipo_res == NULL) {
		yyerror ("operandos de tipos incompativeis.");
		return (NULL);
	}
	return (tipo_res);		
}

/* ----------------------------------------------------------------- */
/* expr_ou ::=	expr_ou T_OU expr_ou_excl /*
/* ----------------------------------------------------------------- */

tipo_t *expr_ou (tipo_t *tipo1, tipo_t *tipo2) 
{
	/* Obtencao do tipo de dados do resultado da operacao. */
	tipo_t *tipo_res = tipo_obter_resultante (T_OU, tipo1, tipo2);
	if (tipo_res == NULL) {
		yyerror ("operandos de tipos incompativeis.");
		return (NULL);
	}
	return (tipo_res);		
}

/* ----------------------------------------------------------------- */
/* expr_ou_excl ::=	expr_ou_excl T_OU_EXCL expr_igual /*
/* ----------------------------------------------------------------- */

tipo_t *expr_ou_excl (tipo_t *tipo1, tipo_t *tipo2) 
{
	/* Obtencao do tipo de dados do resultado da operacao. */
	tipo_t *tipo_res = tipo_obter_resultante (T_OU_EXCL, tipo1, tipo2);
	if (tipo_res == NULL) {
		yyerror ("operandos de tipos incompativeis.");
		return (NULL);
	}
	return (tipo_res);		
}

/* ----------------------------------------------------------------- */
/* expr_relac ::= expr_relac T_MENOR expr_soma */
/* ----------------------------------------------------------------- */

tipo_t *expr_relac (int oper, tipo_t *tipo1, tipo_t *tipo2)
{
	/* Obtencao do tipo de dados do resultado da operacao. */
	tipo_t *tipo_res = tipo_obter_resultante (oper, tipo1, tipo2);
	if (tipo_res == NULL) {
		yyerror ("operandos de tipos incompativeis.");
		return (NULL);
	}
	return (tipo_res);		
}

/* ----------------------------------------------------------------- */
/* expr_simpl ::= T_ID */
/* ----------------------------------------------------------------- */

tipo_t *expr_simpl_r5 (char *id)
{
	/* Verificacao da definicao e do tipo do identificador. */
	if (tab_obter_definida (id) == false) {
		yyerror ("variavel usada mas nao definida.");
		return (NULL);
	}
	
	if (tab_obter_tipo_entr (id) != ENTR_VAR) {
		yyerror ("identificador nao se refere a uma variavel.");
		return (NULL);
	}
	
	return (tab_obter_tipo (id));	
}

/* ----------------------------------------------------------------- */
/* expr_soma 	::=	expr_soma T_MAIS expr_mult
				::= expr_soma T_MENOS expr_mult */
/* ----------------------------------------------------------------- */

tipo_t *expr_soma (int oper, tipo_t *tipo1, tipo_t *tipo2)
{
	/* Obtencao do tipo de dados do resultado da operacao. */
	tipo_t *tipo_res = tipo_obter_resultante (oper, tipo1, tipo2);
	if (tipo_res == NULL) {
		yyerror ("operandos de tipos incompativeis.");
		return (NULL);
	}
	return (tipo_res);		
		
}

/* ----------------------------------------------------------------- */
/* expr_unaria ::= oper_unario expr_simpl */
/* ----------------------------------------------------------------- */

tipo_t *expr_unaria (int oper, tipo_t *tipo)
{
	/* Obtencao do tipo de dados do resultado da operacao. */
	tipo_t *tipo_res = tipo_obter_resultante (oper, tipo, NULL);
	if (tipo_res == NULL) {
		yyerror ("operandos de tipos incompativeis.");
		return (NULL);
	}
	return (tipo_res);		
}

/* ----------------------------------------------------------------- */
/* inic ::= T_ID T_ATRIB expr */
/* ----------------------------------------------------------------- */

bool inic (char *id, tipo_t *tipo_val)
{
	/* Verificacao do tipo de entrada do identificador. Para que a
	 * definicao da variavel seja valida e preciso que ela nao tenha
	 * sido declarada anteriormente e que seu identificador nao se
	 * refira a uma funcao. */
	 
	switch (tab_obter_tipo_entr (id)) {
		case ENTR_VAR:
			yyerror ("variavel ja declarada anteriormente.");
			return (false);
		case ENTR_FUNC:
			yyerror ("o identificador nao se refere a variavel.");
			return (false);
		case ENTR_VAZIA:
			tab_atrib_tipo_entr (id, ENTR_VAR);
			tab_definir (id);				
			break;
		default:
			yyerror ("erro interno do compilador.");		
			return (false);
	}
	
	/* Atribuicao do tipo de dados da variavel, se esta ainda nao foi
	 * feita. */
	if (tipo_val != NULL) {
		tab_atrib_tipo (id, tipo_val);
	}
	/* if (tab_atrib_tipo (id, tipo_val) == false) {
		yyerror ("erro interno do compilador.");
		return (false);
	} */
	return (true);
}

/* ----------------------------------------------------------------- */
/* lista_arg	::= lista_arg T_VIRG expr
				::= expr */
/* ----------------------------------------------------------------- */

lista_t *lista_arg (tipo_t *tipo)
{
	/* Validacao de argumentos, */
	if (tipo == NULL) {
		return (NULL);
	}
	
	/* Alocacao de uma nova lista de tipos, se necessario. */
	if (args == NULL) {
		args = lista_criar (sizeof (tipo_t*));
	}
	
	/* Insercao do argumento na lista de identificadores. */
	lista_anexar (args, &tipo);

	return (args);
}

/* ----------------------------------------------------------------- */
/* lista_inic 	::=	lista_inic T_VIRG inic
				::=	inic */
/* ----------------------------------------------------------------- */

bool lista_inic (char *id)
{
	/* Validacao de argumentos, */
	if (id == NULL) {
		return (false);
	}
	
	/* Alocacao de uma nova lista de identificadores, se necessario. */
	if (inics == NULL) {
		inics = lista_criar (sizeof (char*));
	}
	
	/* Insercao do argumento na lista de identificadores. */
	lista_anexar (inics, &id);

	return (true);
}

/* ----------------------------------------------------------------- */
/* raiz		::=	unid_traducao
/* ----------------------------------------------------------------- */

void raiz (bool imprimir_tabela)
{
	printf ("%s\n\n", "ENTRADA ACEITA.");
	if (imprimir_tabela == true) {
		printf ("%s\n\n", "Tabela de simbolos:");
		tab_imprimir();
	}
}


