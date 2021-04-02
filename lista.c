# include "lista.h"
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

/* ================================================================= */
/* INFORMACOES BASICAS DO ARQUIVO. */
/* ================================================================= */

/* DESCRICAO: contem as funcoes que operam sobre uma lista simplesmente
 * encadeada. */
/* CRIADO EM: ?? fev. 2021. */
 
/* ================================================================= */
/* FUNCOES */
/* ================================================================= */

/* ----------------------------------------------------------------- */
/* ALTERAR DADO */
/* ----------------------------------------------------------------- */

bool lista_alterar (lista_t *ptr, size_t pos, void *novo, void *copia)
{
	/* Validacao de argumentos. */
	
	if ((ptr == NULL) || (pos >= ptr->tamanho) || (novo == NULL)) {
		return (false);
	}

	/* Travessia da lista ate a posicao desejada, copia do dado
	 * antigo, que sera substituido, se o usuario assim o quis, e
	 * escrita do novo valor do dado. */

	no_t *temp = ptr->inicial;
	for (size_t i = 0; i < pos; i++) {
		temp = temp->prox;
	}
	
	if (copia != NULL) {
		memcpy (copia, temp->dado, ptr->tam_unit);
	}
	
	memcpy (temp->dado, novo, ptr->tam_unit);

	return (true);
}

/* ----------------------------------------------------------------- */
/* BUSCAR DADO */
/* ----------------------------------------------------------------- */

bool lista_buscar (lista_t *ptr, size_t pos, void *copia)
{
	/* Validacao de argumentos. */
	
	if ((ptr == NULL) || (pos >= ptr->tamanho) ||
		(ptr->inicial == NULL) || (copia == NULL)) {
		return (false);
	}

	/* Travessia da lista ate o no da posicao especificada e copia do
	   dado para o endereco fornecido. */
	
	no_t *temp = ptr->inicial;
	for (size_t i = 0; i < pos; i++) {
		temp = temp->prox;
	}
	memcpy (copia, temp->dado, ptr->tam_unit);

	return (true);
}

/* ----------------------------------------------------------------- */
/* VERIFICAO DA EXISTENCIA DE UM DADOS */
/* ----------------------------------------------------------------- */

bool lista_contem (lista_t *ptr, void *dado, void *copia,
				   bool igual (void *dado1, void *dado2),
				   bool *retorno)
{
	/* Validacao de argumentos */

	if ((igual == NULL) || (dado == NULL) || (copia == NULL)) {
		if (retorno != NULL) {
			*retorno = false;
		}
		return (false);
	}

	/* Travessia da lista. */

	no_t *temp = ptr->inicial;
	
	for (size_t i = 0; i < ptr->tamanho; i++)
	{
		if (igual (dado, temp->dado) == true)
		{
			if (copia != NULL) {
				memcpy (copia, temp->dado, ptr->tam_unit);
			}
			if (retorno != NULL) {
				*retorno = true;
			}
			return (true);
		}
		temp = temp->prox;
	}

	return (false);	
}

/* ----------------------------------------------------------------- */
/* CRIACAO DA LISTA (ALOCACAO E INICIALIZACAO) */
/* ----------------------------------------------------------------- */

lista_t *lista_criar (size_t tam_unit)
{
	/* Validacao de argumentos. */
	
	if (tam_unit == 0) {
		return (NULL);
	}

	/* Alocacao do cabecalho da lista. */

	lista_t *nova = malloc (sizeof (lista_t));
	if (nova == NULL) {
		return (NULL);
	}

	/* Inicializacao dos campos do cabecalho. */

	nova->tam_unit = tam_unit;
	nova->tamanho = 0;
	nova->inicial = NULL;

	return (nova);
}

/* ----------------------------------------------------------------- */
/* DESTRUICAO DA LISTA (LIBERACAO DE TODA MEMORIA OCUPADA). */
/* ----------------------------------------------------------------- */

bool lista_destruir (lista_t **ptr)
{
	/* Validacao de argumentos. */
	
	if (ptr == NULL) {
		return (false);
	}

	/* Liberacao de toda memoria ocupada pela lista e atualizacao do
	 * ponteiro para a lista. */
	
	if (*ptr != NULL) {
		lista_reiniciar (*ptr);
		free (*ptr);
		*ptr = NULL;
	}
	return (true);
}

/* ----------------------------------------------------------------- */
/* DETALHAR LISTA (EXIBIR CAMPOS DO CABECALHO E DADOS ARMAZENADOS) */
/* ----------------------------------------------------------------- */

void lista_detalhar (lista_t *ptr, void (imprimir_dado) (void *dado),
					 char *delim)
{
	/* Exibicao do cabecalho. */

	printf ("Endereco da lista: %p\n", ptr);

	if (ptr == NULL) {
		return;
	}
	
	printf ("Tamanho unitario dos dados: %lu bytes\n", ptr->tam_unit);
	printf ("Tamanho da lista: %lu\n", ptr->tamanho);
	printf ("Endereco do dado inicial: %p\n", ptr->inicial);

	/* Travessia da lista e exibicao dos dados. */
	
	printf ("Dados:\n");

	if (imprimir_dado == NULL) {
		printf ("Impossivel imprimir os dados (funcao de impressao"
				"invalida.)");
		return;
	}
	
	if (ptr->tamanho == 0) {
		printf ("nenhum.\n");
		return;
	}
	
	no_t *temp = ptr->inicial;
	size_t i = 0;

	while (temp != NULL) {
		printf ("dados[%lu] (@%p) = %s", i, temp->dado, delim);
		imprimir_dado (temp->dado);
		temp = temp->prox;
		i++;
	}
}

/* ----------------------------------------------------------------- */
/* INSERIR DADO */
/* ----------------------------------------------------------------- */

bool lista_inserir (lista_t *ptr, void *dado, size_t pos)
{
	/* Validacao de argumentos. */

	if ((ptr == NULL) || (dado == NULL) || (pos > ptr->tamanho)) {
		return (false);
	}

	/* Alocacao do no e de sua regiao de dados e copia do dado para o
	   no. */
	no_t *no = malloc (sizeof (no_t));
	if (no == NULL) {
		return (false);
	}

	no->dado = malloc (ptr->tam_unit);
	if (no->dado == NULL) {
		free (no);
		return (false);
	}
	memcpy (no->dado, dado, ptr->tam_unit);

	/* Insercao do no na lista. */
	
	if (pos == 0) {
		no->prox = ptr->inicial;
		ptr->inicial = no;
		ptr->tamanho++;
		return (true);
	}

	no_t *temp = ptr->inicial;	/* Aponta para o no na posicao
								   anterior a da insercao. */
	for (size_t i = 0; i < pos - 1; i++) {
		temp = temp->prox;
	}
	no->prox = temp->prox;
	temp->prox = no;
	ptr->tamanho++;
	
	return (true);

}

/* ----------------------------------------------------------------- */
/* ITERAR SOBRE A LISTA (APLICAR UMA FUNCAO SOBRE TODOS OS DADOS) */
/* ----------------------------------------------------------------- */

bool lista_iterar (lista_t *ptr,
				   void (funcao) (void *dado, void *args), void *args)
{
	/* Validacao de argumentos. */
	
	if ((ptr == NULL) || (funcao == NULL)) {
		return (false);
	}

	/* Travessia da lista e aplicacao da funcao fornecida ao dado
	   armazenado em cada no. */

	no_t *temp = ptr->inicial;
	while (temp != NULL) {
		funcao (temp->dado, args);
		temp = temp->prox;
	}
	return (true);
}

/* ----------------------------------------------------------------- */
/* CONTAR OCORRENCIAS DE UM DADO */
/* ----------------------------------------------------------------- */

size_t lista_ocorrencias (lista_t *ptr, void *dado,
						  bool (igual) (void *dado1, void *dado2),
						  size_t **posicoes, bool *retorno)
{
	/* Validacao de argumentos */

	if ((ptr == NULL) || (dado == NULL) || (igual == NULL)) {
		if (retorno != NULL) {
			*retorno = false;
		}
		return (SIZE_MAX);
	}

	/* Alocacao da lista que armazena as posicoes do dado. */

	lista_t *lista = NULL;
	if ((posicoes != NULL) && (*posicoes != NULL)) {
		lista = lista_criar (sizeof (size_t));
	}

	/* Travessia da lista e contagem das ocorrencias do dado. */

	size_t ocorrencias = 0;
	no_t *temp = ptr->inicial;
	
	for (size_t i = 0; i < ptr->tamanho; i++)
	{
		if (igual (dado, temp->dado) == true) {
			ocorrencias++;
			if (lista != NULL) {
				lista_anexar (lista, &i);
			}
		}
		temp = temp->prox;
	}

	/* Se o usuario deseja saber as posicoes onde o dado esta,
	 * transformamos a lista de posicoes num vetor cujo endereco e
	 * salvo no endereco fornecido. */

	if (lista != NULL) {
		*posicoes = lista_para_vetor (lista);
		lista_destruir (&lista);
	}

	return (ocorrencias);
}

/* ----------------------------------------------------------------- */
/* ORDENAR LISTA */
/* ----------------------------------------------------------------- */

bool lista_ordenar (lista_t *ptr, int (comparar)
					(const void *dado1, const void *dado2))
{
	/* Validacao de argumentos. */
	
	if ((ptr == NULL) || (comparar == NULL)) {
		return (false);
	}

	/* Geracao de um vetor com os dados da lista. */

	void *vetor = lista_para_vetor (ptr);
	if (vetor == NULL) {
		return (false);
	}

	/* Ordenacao do vetor. */

	qsort (vetor, ptr->tamanho, ptr->tam_unit, comparar);

	/* Reiniciamos a lista e inserimos seus dados ordenados. */
	
	size_t tamanho = ptr->tamanho;
	size_t desloc = 0;
	lista_reiniciar (ptr);
	
	for (size_t i = 0; i < tamanho; i++) {
		lista_anexar (ptr, vetor + desloc);
		desloc += ptr->tam_unit;
	}

	free (vetor);
	return (true);
}


/* ----------------------------------------------------------------- */
/* PARA VETOR (GERAR UM VETOR COM OS DADOS DA LISTA) */
/* ----------------------------------------------------------------- */

void *lista_para_vetor (lista_t *ptr)
{
	/* Validacao de argumentos. */
	
	if (ptr == NULL) {
		return (NULL);
	}

	/* Alocacao do vetor de dados. */

	void *vetor = calloc (ptr->tamanho, ptr->tam_unit);
	if (vetor == NULL) {
		return (NULL);
	}

	/* Copia dos dados da lista para o vetor. */

	no_t *temp = ptr->inicial;
	size_t desloc = 0;

	while (temp != NULL) {
		memcpy (vetor + desloc, temp->dado, ptr->tam_unit);
		temp = temp->prox;
		desloc += ptr->tam_unit;
	}	
	return (vetor);
}


/* ----------------------------------------------------------------- */
/* REINICIAR LISTA (REMOVER TODOS OS DADOS) */
/* ----------------------------------------------------------------- */

bool lista_reiniciar (lista_t *ptr)
{
	/* Validacao de argumentos. */
	
	if (ptr == NULL) {
		return (false);
	}

	/* Travessia da lista, liberacao de toda memoria ocupada por nos
	 * e dados e atualizacao do cabecalho. */
	
	no_t *temp = ptr->inicial;
	no_t *prox;
	
	while (temp != NULL) {
		free (temp->dado);
		prox = temp->prox;
		free (temp);
		temp = prox;
	}
	ptr->inicial = NULL;
	ptr->tamanho = 0;

	return (true);
}

/* ----------------------------------------------------------------- */
/* REMOVER DADO */
/* ----------------------------------------------------------------- */

bool lista_remover (lista_t *ptr, size_t pos, void *copia)
{
	if ((ptr == NULL) || (pos >= ptr->tamanho)) {
		return (false);
	}

	/* Manutencao da consistencia da listaa. Se o dado a remover se
	 * encontra na primeira posicao e necessario atualizar o ponteiro
	 * para o inicio da lista. Caso contrario, e preciso buscar o
	 * elemento anterior ao que sera removido e acertar seu ponteiro
	 * para o proximo elemento da lista. */

	no_t *alvo;
	if (pos == 0) {
		alvo = ptr->inicial;
		ptr->inicial = alvo->prox;
	}
	else {
		no_t *temp = ptr->inicial;
		for (size_t i = 0; i < pos - 1; i++) {
			temp = temp->prox;
		}
		alvo = temp->prox;
		temp->prox = alvo->prox;
	}

	/* Copia do dado para o endereco especificado, se o usuario assim
	 * o desejou, liberacao da memoria ocupada pelo dado e por seu
	 * no e atualizacao do tamanho da lista. */
	
	if (copia != NULL) {
		memcpy (copia, alvo->dado, ptr->tam_unit);			
	}
	free (alvo->dado);
	free (alvo);
	ptr->tamanho--;
		
	return (true);
}

/* ----------------------------------------------------------------- */
/* OBTER TAMANHO DA LISTA (QUANTIDADE DE DADOS ARMAZENADOS) */
/* ----------------------------------------------------------------- */

size_t lista_tamanho (lista_t *ptr, bool *retorno)
{
	if (ptr == NULL) {
		if (retorno != NULL) {
			*retorno = false;
		}
		return (SIZE_MAX);
	}
	else {
		if (retorno != NULL) {
			*retorno = true;
		}
		return (ptr->tamanho);
	}
}

/* ----------------------------------------------------------------- */
/* PARA LISTA (GERAR UMA LISTA COM TODOS OS DADOS DE UM VETOR) */
/* ----------------------------------------------------------------- */

lista_t *vetor_para_lista (void *vetor, size_t tamanho, size_t tam_unit)
{
	/* Validacao de argumentos. */
	
	if ((vetor == NULL) || (tamanho == 0) || (tam_unit == 0)) {
		return (NULL);
	}

	/* Criacao da nova lista. */

	lista_t *lista = lista_criar (tam_unit);
	if (lista == NULL) {
		return (NULL);
	}

	/* Insercao dos dados do vetor na lista. */

	size_t desloc = 0;
	for (size_t i = 0; i < tamanho; i++) {
		if (lista_anexar (lista, vetor + desloc) == false) {
			lista_destruir (&lista);
			return (NULL);
		}
		desloc += tam_unit;
	}

	return (lista);
}


/* ================================================================= */
