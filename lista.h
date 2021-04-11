#ifndef LISTA_H
#define LISTA_H

#include "lista-defs.h"
#include <stdbool.h>
#include <stdlib.h>

/* ================================================================= */
/* INFORMACOES BASICAS DO ARQUIVO. */
/* ================================================================= */

/* DESCRICAO: contem as assinaturas das funcoes que manipulam uma
 * lista simplesmente encadeada. */
/* CRIADO EM: ?? fev. 2021. */

/* ================================================================= */
/* FUNCOES */
/* ================================================================= */

bool lista_alterar(lista_t *ptr, size_t pos, void *novo, void *copia);
bool lista_buscar(lista_t *ptr, size_t pos, void *copia);
bool lista_contem(lista_t *ptr, void *dado, void *copia,
                  bool igual(void *dado1, void *dado2),
                  bool *retorno);
lista_t *lista_criar(size_t tam_unit);
bool lista_destruir(lista_t **ptr);
void lista_detalhar(lista_t *ptr, void(imprimir_dado)(void *dado),
                    char *delim);
bool lista_inserir(lista_t *ptr, void *dado, size_t pos);
bool lista_iterar(lista_t *ptr,
                  void(funcao)(void *dado, void *args), void *args);
size_t lista_ocorrencias(lista_t *ptr, void *dado,
                         bool(igual)(void *dado1, void *dado2),
                         size_t **posicoes, bool *retorno);
bool lista_ordenar(lista_t *ptr, int(comparar)(const void *dado1, const void *dado2));
void *lista_para_vetor(lista_t *ptr);
bool lista_reiniciar(lista_t *ptr);
bool lista_remover(lista_t *ptr, size_t pos, void *copia);
size_t lista_tamanho(lista_t *ptr, bool *retorno);
lista_t *vetor_para_lista(void *vetor, size_t tamanho,
                          size_t tam_unit);

#define lista_anexar(ptr, dado) lista_inserir((ptr), (dado), lista_tamanho((ptr), NULL))
#define lista_prefixar(ptr, dado) lista_inserir((ptr), (dado), 0)

/* ================================================================= */

#endif
