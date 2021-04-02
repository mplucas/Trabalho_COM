# include "entr.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "tabsimb-defs.h"
# include "tabsimb.h"

/* ================================================================= */
/* INFORMACOES BASICAS DO ARQUIVO */
/* ================================================================= */

/* DESCRICAO: contem as funcoes relativas a uma entrada na tabela de
   simbolos. */
/* CRIADO EM: 15 mar. 2021. */

/* ================================================================= */
/* ASSINATURAS DAS FUNCOES ESTATICAS */
/* ================================================================= */

static void entr_imprimir_params (entr_t *entr);

/* ================================================================= */
/* MAIN (usado para fins de teste) */
/* ================================================================= */

// # define TESTE_ENTR

# ifdef TESTE_ENTR

int main (void)
{
	entr_t *entr_var = entr_criar ("querida_variavel");
	entr_atrib_tipo_entr (entr_var, ENTR_VAR);
	entr_atrib_linha (entr_var, 10);
	entr_atrib_coluna (entr_var, 23);
	entr_atrib_tipo (entr_var, tipo_obter ("int"));
	int valor_var = 50;
	entr_atrib_valor (entr_var, &valor_var);
	entr_imprimir (entr_var);

	entr_t *entr_func = entr_criar ("querida_funcao");
	entr_atrib_tipo_entr (entr_func, ENTR_FUNC);
	entr_atrib_linha (entr_func, 27);
	entr_atrib_coluna (entr_func, 5);
	entr_atrib_tipo (entr_func, tipo_obter ("bool"));
	bool valor_func = true;
	entr_atrib_valor (entr_func, &valor_func);
	entr_marcar_como_definida (entr_func);
	tipo_t *param = tipo_obter ("char");
	entr_inserir_param (entr_func, &param);
	param = tipo_obter ("int");
	entr_inserir_param (entr_func, &param);
	param = tipo_obter ("float");
	entr_inserir_param (entr_func, &param);
	entr_imprimir (entr_func);

	return (0);
}

# endif

/* ================================================================= */
/* FUNCOES */
/* ================================================================= */

/* ----------------------------------------------------------------- */
/* ATRIBUIR COLUNA A UMA ENTRADA */
/* ----------------------------------------------------------------- */

bool entr_atrib_coluna (entr_t *entr, int coluna)
{
	/* Validacao de argumentos */
	if (coluna <= 0) {
		return (false);
	}
	
	/* Atribuicao redundante. */
	if (entr->coluna == coluna) {
		return (true);
	}

	/* Atribuicao da coluna ao campo. */
	if (entr->coluna != -1) {
		return (false);
	}
	entr->coluna = coluna;
	return (true);	
}

/* ----------------------------------------------------------------- */
/* ATRIBUIR LINHA A UMA ENTRADA */
/* ----------------------------------------------------------------- */

bool entr_atrib_linha (entr_t *entr, int linha)
{
	/* Validacao de argumentos. */
	if (linha <= 0) {
		return (false);
	}
	
	/* Atribuicao redundante. */
	if (entr->linha == linha) {
		return (true);
	}

	/* Atribuicao da linha ao campo se esta ainda nao foi feita. */
	if (entr->linha != -1) {
		return (false);
	}
	entr->linha = linha;
	return (true);
}

/* ----------------------------------------------------------------- */
/* ATRIBUIR TIPO DE DADOS A UMA ENTRADA */
/* ----------------------------------------------------------------- */

bool entr_atrib_tipo (entr_t *entr, tipo_t *tipo)
{
	/* Validacao de argumentos. */
	if ((tipo == NULL)) {
		return (false);
	}
	
	/* Não existe variavel de tipo void. */
	if ((entr->tipo_entr == ENTR_VAR) && (tipo == tipo_obter ("void"))) {
		return (false);
	}
	
	/* Atribuicao redundante. */
	if (entr->tipo == tipo) {
		return (true);
	}

	/* Atribuicao do tipo ao campo se esta ainda nao foi feita. */
	if ((entr->tipo == tipo_obter ("bool")) || 
		(entr->tipo == tipo_obter ("char"))) {
		return (false);	
	}
	
	entr->tipo = tipo;
	return (true);	
}

/* ----------------------------------------------------------------- */
/* ATRIBUIR TIPO DE ENTRADA A UMA ENTRADA */
/* ----------------------------------------------------------------- */

bool entr_atrib_tipo_entr (entr_t *entr, int tipo)
{
	/* Atribuicao redundante. */
	if (entr->tipo_entr == tipo) {
		return (true);
	}
		
	/* Validacao de argumentos. */
	if ((tipo != ENTR_VAR) && (tipo != ENTR_FUNC)) {
		return (false);
	}
	
	/* Nao existe variavel de tipo void. */
	if ((entr->tipo == tipo_obter ("void")) && (tipo == ENTR_VAR)) {
		return (false);
	}

	/* Atribuicao do tipo de entrada se esta ainda nao foi feita. */
	if ((entr->tipo_entr != ENTR_VAZIA)) {
		return (false);
	}
	entr->tipo_entr = tipo;
	return (true);
}

/* ----------------------------------------------------------------- */
/* ATRIBUIR VALOR A UMA ENTRADA */
/* ----------------------------------------------------------------- */

bool entr_atrib_valor (entr_t *entr, void *valor)
{
	/* Validacao de argumentos. */
	if (valor == NULL) {
		return (false);
	}

	/* Alocacao de memoria para o valor. */
	size_t bytes = tipo_obter_bytes (entr->tipo);
	if (entr->valor == NULL) {
		entr->valor = malloc (bytes);
		if (entr->valor == NULL) {
			return (false);
		}
	}

	/* Atribuicao do valor ao campo da entrada. */
	memcpy (entr->valor, valor, bytes);
	return (true);
}

/* ----------------------------------------------------------------- */
/* CRIAR ENTRADA */
/* ----------------------------------------------------------------- */

entr_t *entr_criar (char *id)
{
	/* Alocacao de memoria para a entrada. */
	entr_t *entr = malloc (sizeof (entr_t));
	if (entr == NULL) {
		return (NULL);
	}

	/* Alocacao de memoria para o identificador. */
	entr->id = calloc (strlen (id) + 1, sizeof (char));
	if (entr->id == NULL) {
		return (NULL);
	}

	/* Inicializacao dos campos da entrada. */
	strcpy (entr->id, id);	
	entr->tipo_entr = ENTR_VAZIA;
	entr->coluna = -1;
	entr->linha = -1;
	entr->tipo = NULL;
	entr->valor = NULL;
	entr->params = NULL;
	entr->definida = false;
	entr->declarada = false;
	
	return (entr);
}

/* ----------------------------------------------------------------- */
/* IMPRIMIR ENTRADA */
/* ----------------------------------------------------------------- */

void entr_imprimir (entr_t *entr)
{
	/* Entrada nao alocada. */
	if (entr == NULL) {
		printf ("%s\n", "Entrada nao alocada.");
		return;
	}

	/* Endereco da entrada. */
	printf ("Entrada @ %p\n", entr);

	/* Tipo da entrada. */
	printf ("%s", "Tipo da entrada = ");
	switch (entr->tipo_entr) {
	case ENTR_VAZIA: printf ("%s\n", "vazia."); break;
	case ENTR_VAR: printf ("%s\n", "variavel"); break;
	case ENTR_FUNC: printf ("%s\n", "funcao"); break;
	default: printf ("%s\n", "nao identificado"); break;
	}

	/* Identificador. */
	printf ("ID: %s\n", entr->id);

	/* Tipo de dados. */
	tipo_imprimir (entr->tipo);

	/* Valor. */
	printf ("%s", "Valor: ");
	tipo_imprimir_valor (entr->tipo, entr->valor);
	printf ("\n");

	/* Indicador de definicao da variavel ou funcao. */
	printf ("Esta definida? %s\n", entr->definida ? "Sim": "Nao");
	
	/* Indicacao de declaracao da variavel ou funcao. */
	printf ("Esta declarada? %s\n", entr->declarada ? "Sim": "Nao");

	/* Se a entrada se referir a uma funcao imprimimos tambem sua 
		lista de parametros. */
	
	if (entr->tipo_entr == ENTR_FUNC)
	{
		printf ("Parametros: ");
		entr_imprimir_params (entr);
	}

	/* Posicao da primeira aparicao da variavel ou funcao no codigo. */
	printf ("Posicao: (L%d, C%d)\n", entr->linha, entr->coluna);

	printf ("%s", "\n");
}

/* ----------------------------------------------------------------- */
/* IMPRIMIR LISTA DE PARAMETROS DE UMA FUNCAO */
/* ----------------------------------------------------------------- */

static void entr_imprimir_params (entr_t *entr)
{
	/* Se a entrada se referir a uma variavel... */
	if (entr->tipo_entr != ENTR_FUNC) {
		printf ("Variavel nao tem parametro!");
		return;
	}
	
	/* Lista de parametros. */
	if (entr->params == NULL) {
		printf ("nenhum.\n");
		return;
	}

	/* Travessia da lista de parametros. */	
	size_t qtde_params = lista_tamanho (entr->params, NULL);
	tipo_t *tipo;
	
	for (size_t i = 0; i < qtde_params - 1; i++) {
		lista_buscar (entr->params, i, &tipo); 
		printf ("%s, ", tipo_obter_nome (tipo));
	}
	lista_buscar (entr->params, qtde_params - 1, &tipo);
	printf ("%s.\n", tipo_obter_nome (tipo));	
}

/* ----------------------------------------------------------------- */
/* INSERIR PARAMETRO NUMA ENTRADA DE FUNCAO */
/* ----------------------------------------------------------------- */

bool entr_inserir_param (entr_t *entr, tipo_t **param)
{
	/* Verificando se a entrada fornecida se refere a uma funcao. */
	if (entr->tipo_entr != ENTR_FUNC) {
		return (false);
	}

	/* Validacao de argumentos */
	if ((param == NULL) || (*param == NULL)) {
		return (false);
	}

	/* Criacao da lista de parametros, se necessario. */
	if (entr->params == NULL) {
		entr->params = lista_criar (sizeof (tipo_t*));
		if (entr->params == NULL) {
			return (false);
		}
	}

	/* Insercao do parametro na lista. */
	return (lista_anexar (entr->params, param));
}

/* ----------------------------------------------------------------- */
/* MARCAR ENTRADA DE FUNCAO COMO DEFINIDA */
/* ----------------------------------------------------------------- */

void entr_marcar_como_declarada (entr_t *entr)
{
	entr->declarada = true;
}


/* ----------------------------------------------------------------- */
/* MARCAR ENTRADA DE FUNCAO COMO DEFINIDA */
/* ----------------------------------------------------------------- */

void entr_marcar_como_definida (entr_t *entr)
{
	entr->declarada = true;
	entr->definida = true;
}

/* ----------------------------------------------------------------- */
/* OBTER LINHA DE UMA ENTRADA */
/* ----------------------------------------------------------------- */

int entr_obter_coluna (entr_t *entr)
{
	return (entr->coluna);
}

/* ----------------------------------------------------------------- */
/* OBTER FLAG DE DEFINICAO DE UMA FUNCAO */
/* ----------------------------------------------------------------- */

bool entr_obter_declarada (entr_t *entr)
{
	return (entr->declarada);
}	

/* ----------------------------------------------------------------- */
/* OBTER FLAG DE DEFINICAO DE UMA FUNCAO */
/* ----------------------------------------------------------------- */

bool entr_obter_definida (entr_t *entr)
{
	return (entr->definida);
}

/* ----------------------------------------------------------------- */
/* OBTER LINHA DE UMA ENTRADA */
/* ----------------------------------------------------------------- */

int entr_obter_linha (entr_t *entr)
{
	return (entr->linha);
}

/* ----------------------------------------------------------------- */
/* OBTER UM PARAMETRO DA LISTA DE PARAMETROS.  */
/* ----------------------------------------------------------------- */

tipo_t *entr_obter_param (entr_t *entr, size_t pos)
{
	/* Lista de parametros vazia. */
	if (entr->params == NULL) {
		return (NULL);
	}

	/* Busca pelo parametro. Se a posicao fornecida e invalida
	   retornamos NULL. */
	tipo_t *tipo;
	if (lista_buscar (entr->params, pos, &tipo) == false) {
		return (NULL);
	}

	return (tipo);
}

/* ----------------------------------------------------------------- */
/* OBTER QUANTIDADE DE PARAMETROS DA FUNCAO */
/* ----------------------------------------------------------------- */

size_t entr_obter_qtde_params (entr_t *entr)
{
	if (entr->params == NULL) {
		return (0);
	}
	return (lista_tamanho (entr->params, NULL));
}

/* ----------------------------------------------------------------- */
/* OBTER TIPO DE DADOS DE UMA ENTRADA */
/* ----------------------------------------------------------------- */

tipo_t *entr_obter_tipo (entr_t *entr)
{
	return (entr->tipo);	
}

/* ----------------------------------------------------------------- */
/* OBTER TIPO DA ENTRADA */
/* ----------------------------------------------------------------- */

int entr_obter_tipo_entr (entr_t *entr)
{
	return (entr->tipo_entr);
}

/* ----------------------------------------------------------------- */
/* OBTER VALOR DE UMA ENTRADA */
/* ----------------------------------------------------------------- */

void *entr_obter_valor (entr_t *entr)
{
	return (entr->valor);
}
