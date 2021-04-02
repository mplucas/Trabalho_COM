# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "tabsimb-defs.h"
# include "tabsimb.h"
# include "trabalho.tab.h"

# define QTDE_TIPOS 5
// # define TESTE_TIPO

/* ================================================================= */
/* INFORMACOES BASICAS DO ARQUIVO */
/* ================================================================= */

/* DESCRICAO: contem as funcoes que manipulam o tipo de dados que
 * representa os tipos de dados da linguagem.  */
/* CRIADO EM: 07 mar. 2021. */

/* ================================================================= */
/* VARIAVEIS GLOBAIS */
/* ================================================================= */

static tipo_t **tipos = NULL;

/* ================================================================= */
/* CONSTANTES UTEIS. */
/* ================================================================= */

enum nometipo_t {
	TIPO_BOOL, TIPO_CHAR, TIPO_FLOAT, TIPO_INT, TIPO_VOID, 
	TIPO_NULO = -1
};


/* ================================================================= */
/* ASSINATURAS DAS FUNCOES PRIVADAS */
/* ================================================================= */

static bool tipo_atrib_bytes (tipo_t *tipo, size_t bytes);
static tipo_t *tipo_criar (char *nome);
static void tipo_destruir (tipo_t **tipo);
static void tipos_imprimir (void);
static void tipos_inicializar (void);
static int tipo_obter_codigo (tipo_t *tipo);

/* ================================================================= */
/* MAIN (utilizado para testes) */
/* ================================================================= */

# ifdef TESTE_TIPO

int main (void)
{
	tipos_inicializar();
	tipos_imprimir();
	tipos_destruir();
	tipos_imprimir();
	return (0);
}

# endif

/* ================================================================= */
/* FUNCOES */
/* ================================================================= */

/* ----------------------------------------------------------------- */
/* CRIAR TIPO */
/* ----------------------------------------------------------------- */

static tipo_t *tipo_criar (char *nome)
{
	if (nome == NULL) {
		return (NULL);
	}

	tipo_t *tipo = malloc (sizeof (tipo_t));
	if (tipo == NULL) {
		return (NULL);
	}

	tipo->nome = malloc (strlen (nome) + 1);
	if (tipo->nome == NULL) {
		free (tipo);
		return (NULL);
	}

	strcpy (tipo->nome, nome);
	return (tipo);
}

/* ----------------------------------------------------------------- */
/* ATRIBUIR TAMANHO DO TIPO */
/* ----------------------------------------------------------------- */

static bool tipo_atrib_bytes (tipo_t *tipo, size_t bytes)
{
	if (bytes == 0) {
		return (false);
	}

	tipo->bytes = bytes;
	return (true);
}

/* ----------------------------------------------------------------- */
/* DESTRUIR UM TIPO */
/* ----------------------------------------------------------------- */

static void tipo_destruir (tipo_t **tipo)
{
	free ((*tipo)->nome);
	(*tipo)->nome = NULL;
	
	free (*tipo);
	*tipo = NULL;
}

/* ----------------------------------------------------------------- */
/* DESTRUIR VETOR DE TIPOS */
/* ----------------------------------------------------------------- */

void tipos_destruir (void)
{
	for (int i = 0; i < QTDE_TIPOS; i++) {
		if (tipos[i] == NULL) {
			break;
		}
		tipo_destruir (&tipos[i]);
	}
	free (tipos);
	tipos = NULL;
}

/* ----------------------------------------------------------------- */
/* IMPRIMIR TIPO */
/* ----------------------------------------------------------------- */

void tipo_imprimir (tipo_t *tipo)
{
	printf ("%s", "Tipo: ");
	if (tipo != NULL) {
		printf ("%s (%lu bytes) \n", tipo->nome, tipo->bytes);
	}
	else {
		printf ("%s\n", "(null)");
	}
}

/* ----------------------------------------------------------------- */
/* IMPRIMIR VALOR DE UM TIPO */
/* ----------------------------------------------------------------- */

void tipo_imprimir_valor (tipo_t *tipo, void *valor)
{
	if (valor == NULL) {
		printf ("(null)");
		return;
	}
	
	for (int i = 0; i < QTDE_TIPOS; i++)
	{
		if (tipos[i] == tipo)
		{
			switch (i) {
			case TIPO_BOOL:
				printf ("%s", *((bool*) valor) == 1 ? "true" : "false");
				break;
			case TIPO_CHAR:
				printf ("%c", *((char*) valor));
				break;
			case TIPO_FLOAT:
				printf ("%f", *((float*) valor));
				break;
			case TIPO_INT:
				printf ("%d", *((int*) valor));
				break;
			}
		}
	}
}

/* ----------------------------------------------------------------- */
/* IMPRIMIR VETOR DE TIPOS */
/* ----------------------------------------------------------------- */

static void tipos_imprimir (void)
{
	if (tipos == NULL) {
		printf ("Vetor de tipos nulo.\n\n");
		return;
	}
	
	for (int i = 0; i < QTDE_TIPOS; i++) {
		tipo_imprimir (tipos[i]);
	}
}

/* ----------------------------------------------------------------- */
/* INICIALIZACAO DO VETOR COM OS TIPOS DA LINGUAGEM */
/* ----------------------------------------------------------------- */

static void tipos_inicializar (void)
{
	/* Alocacao da memoria para o vetor de tipos. */
	tipos = calloc (QTDE_TIPOS, sizeof (tipo_t*));
	if (tipos == NULL) {
		return;
	}

	/* Criacao de cada elemento do vetor. */
	for (int i = 0; i < QTDE_TIPOS; i++)
	{	
		switch (i) {
		case TIPO_BOOL: tipos[i] = tipo_criar ("bool"); break;
		case TIPO_CHAR: tipos[i] = tipo_criar ("char"); break;
		case TIPO_FLOAT: tipos[i] = tipo_criar ("float"); break;
		case TIPO_INT: tipos[i] = tipo_criar ("int"); break;
		case TIPO_VOID: tipos[i] = tipo_criar ("void"); break;
		default:
			fprintf (stderr, "ERRO @ tipo_obter_vetor().\n");
			exit (1);
		}
	}

	/* Inicialiazacao do campo de tamanho do tipo de dados para cada
	tipo do vetor.
	Verificamos, antes da atribuicao, se a criacao do tipo foi bem
	sucedida. Em caso negativo paralisamos o programa, uma vez que os
	dados referentes aos tipos de dados da linguagem precisam estar
	disponiveis durante toda a execucao do compilador para que ela
	seja bem sucedida. */
	
	for (int i = 0; i < QTDE_TIPOS; i++)
	{
		if (tipos[i] == NULL) {
			tipos_destruir();
			return;
		}
		
		switch (i) {
		case TIPO_BOOL: tipo_atrib_bytes (tipos[i], sizeof (bool));
			break;
		case TIPO_CHAR: tipo_atrib_bytes (tipos[i], sizeof (char));
			break;
		case TIPO_FLOAT: tipo_atrib_bytes (tipos[i], sizeof (float));
			break;
		case TIPO_INT: tipo_atrib_bytes (tipos[i], sizeof (int));
			break;
		case TIPO_VOID: tipo_atrib_bytes (tipos[i], sizeof (void));
			break;
		}	
	}
}

/* ----------------------------------------------------------------- */
/* OBTER UM TIPO A PARTIR DO SEU NOME */
/* ----------------------------------------------------------------- */

tipo_t *tipo_obter (char *nome)
{
	if (nome == NULL) {
		return (NULL);
	}

	if (tipos == NULL) {
		tipos_inicializar();
	}

	for (int i = 0; i < QTDE_TIPOS; i++) {
		if (strcmp (nome, tipos[i]->nome) == 0) {
			return (tipos[i]);
		}
	}
	return (NULL);
}

/* ----------------------------------------------------------------- */
/* OBTER TAMANHO DE UM TIPO */
/* ----------------------------------------------------------------- */

size_t tipo_obter_bytes (tipo_t *tipo) {
	return (tipo->bytes);
}

/* ----------------------------------------------------------------- */
/* OBTER NOME DE UM TIPO */
/* ----------------------------------------------------------------- */

char* tipo_obter_nome (tipo_t *tipo) {
	return (tipo->nome);
}

/* ----------------------------------------------------------------- */
/* OBTER O CODIGO (CONSTANTE INTEIRA ENUMERADA) DE UM TIPO */
/* ----------------------------------------------------------------- */

static int tipo_obter_codigo (tipo_t *tipo) 
{
	for (int i = 0; i < QTDE_TIPOS; i++) {
		if (tipo == tipos[i]) {
			return (i);
		}
	}
	return (TIPO_NULO);
}

/* ----------------------------------------------------------------- */
/* OBTER TIPO DE DADO DO RESULTADO DE UMA OPERACAO BINARIA */
/* ----------------------------------------------------------------- */

tipo_t *tipo_obter_resultante (int oper, tipo_t *tipo1, tipo_t *tipo2)
{	
	/* Obtencao das constantes relativas a cada um dos tipos. */
	int cod1 = tipo_obter_codigo (tipo1);
	if (cod1 == TIPO_NULO) {
		return (NULL);
	}
	
	/* Se o segundo argumento vale NULL entao o usuario deseja saber
	 * qual e o tipo resultante de uma operacao unaria cujo tipo do
	 * operando e igual ao do primeiro argumento. Ou seja, o tipo
	 * resultante e o mesmo do primeiro argumento. */ 
	
	if (tipo2 == NULL) 
	{
		switch (oper) {
			case T_MAIS:
			case T_MENOS:
				switch (cod1) {
					case TIPO_INT:		return (tipos[TIPO_INT]);
					case TIPO_FLOAT:	return (tipos[TIPO_FLOAT]);
					default:			return (NULL);
				}
			case T_NAO:
				switch (cod1) {
					case TIPO_BOOL:		return (tipos[TIPO_BOOL]);
					default:				return (NULL);
				}
			default:
				return (NULL);
		}
	}
	
	int cod2 = tipo_obter_codigo (tipo2);
	if (cod2 == TIPO_NULO) {
		return (NULL);
	}
	
	/* Retorno do tipo resultante quando ha operacoes binarias. */	
	switch (oper) {
		case T_MAIS:
		case T_MENOS:
		case T_DIV:
		case T_VEZES:
			switch (cod1) {
				case TIPO_INT:
					switch (cod2) {
						case TIPO_INT:		return (tipos[TIPO_INT]);
						case TIPO_FLOAT: 	return (tipos[TIPO_FLOAT]);
						default:			return (NULL);
					}
				case TIPO_FLOAT:
					switch (cod2) {
						case TIPO_INT:		return (tipos[TIPO_FLOAT]);
						case TIPO_FLOAT:	return (tipos[TIPO_FLOAT]);
						default:			return (NULL);
					}
				default:					return (NULL);
			}
		case T_RESTO:
			switch (cod1) {
				case TIPO_INT:
					switch (cod2) {
						case TIPO_INT:		return (tipos[TIPO_INT]);
						default:			return (NULL);
					}
				default:					return (NULL);
			}
		case T_E:
		case T_OU:
		case T_OU_EXCL:
			switch (cod1) {
				case TIPO_BOOL:
					switch (cod2) {
						case TIPO_BOOL: 	return (tipos[TIPO_BOOL]);
						default:			return (NULL);
					}
				default:					return (NULL);
			}
		case T_DIFER:
		case T_IGUAL:
				return ((cod1 == cod2) ? (tipos[TIPO_BOOL]) : NULL);
		case T_MENOR:
		case T_MAIOR:
		case T_MENOR_IGUAL:
		case T_MAIOR_IGUAL:
			switch (cod1) {
				case TIPO_INT:
					switch (cod2) {
						case TIPO_INT:		return (tipos[TIPO_BOOL]);
						case TIPO_FLOAT:	return (tipos[TIPO_BOOL]);
						default:			return (NULL);
					}
				case TIPO_FLOAT:
					switch (cod2) {
						case TIPO_INT:		return (tipos[TIPO_BOOL]);
						case TIPO_FLOAT:	return (tipos[TIPO_BOOL]);
						default:			return (NULL);
					}
				default:					return (NULL);
			}
		case T_ATRIB:
		switch (cod1) {
			case TIPO_BOOL:
				switch (cod2) {
					case TIPO_BOOL:		return (tipos[TIPO_BOOL]);
					default:			return (NULL);		
				}
			case TIPO_CHAR:
				switch (cod2) {
					case TIPO_CHAR:		return (tipos[TIPO_CHAR]);
					default:			return (NULL);		
				}
			case TIPO_FLOAT:
				switch (cod2) {
					case TIPO_INT:		return (tipos[TIPO_FLOAT]);
					case TIPO_FLOAT:	return (tipos[TIPO_FLOAT]);
					default:			return (NULL);
				}
			case TIPO_INT:
				switch (cod2) {
					case TIPO_INT:		return (tipos[TIPO_INT]);
					case TIPO_FLOAT:	return (tipos[TIPO_INT]);
					default:			return (false);
				}
			default:					return (false);
		}
		default:						return (NULL);
	}
}


/* ----------------------------------------------------------------- */
/* OBTER VETOR COM TODOS OS TIPOS. */
/* ----------------------------------------------------------------- */

/* tipo_t **tipos_obter (void) {
	return (tipos);
} */

/* ----------------------------------------------------------------- */
/* OBTER QUANTIDADE DE TIPOS. */
/* ----------------------------------------------------------------- */

size_t tipos_obter_qtde (void) {
	return (QTDE_TIPOS);
}

/* ----------------------------------------------------------------- */
/* VERIFICAR COMPATIBILIDADE DOS OPERANDOS DE UMA ATRIBUICAO */ 
/* ----------------------------------------------------------------- */

bool tipo_validar_atrib (tipo_t *tipo_esq, tipo_t *tipo_dir) 
{
	/* Considere uma atribuicao comum: variavel = valor. tipo_esq
	 * corresponde ao tipo da variavel e tipo_dir ao do valor. */

	/* Uma atribuicao e valida em duas condicoes: (i) os tipos dos
	 * operando sao iguais; (ii) o tipo de um operando e float e o
	 * outro e int. */
	 
	int cod_esq = tipo_obter_codigo (tipo_esq);
	int cod_dir = tipo_obter_codigo (tipo_dir);
	
	switch (cod_esq) {
		case TIPO_BOOL:
			switch (cod_dir) {
				case TIPO_BOOL:		return (true);
				default:			return (false);		
			}
		case TIPO_CHAR:
			switch (cod_dir) {
				case TIPO_CHAR:		return (true);
				default:			return (false);		
			}
		case TIPO_FLOAT:
		case TIPO_INT:
			switch (cod_dir) {
				case TIPO_INT:		return (true);
				case TIPO_FLOAT:	return (true);
				default:			return (false);
			}
		default:					return (false);
	}
}
