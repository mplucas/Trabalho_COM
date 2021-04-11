#ifndef TABSIMB_INTERFACE_H
#define TABSIMB_INTERFACE_H

#include "tabsimb-defs.h"

/* ================================================================= */
/* INFORMACOES BASICAS DO ARQUIVO */
/* ================================================================= */

/* DESCRICAO: contem as assinaturas das funcoes que implementam
   a tabela de simbolos e funcoes auxiliares. */
/* CRIADO EM: 07 mar. 2021. */

/* ================================================================= */
/* CONSTANTES UTEIS */
/* ================================================================= */

/* Tipos de entrada na tabela de simbolos. As entradas podem se referir
 * a variaveis, funcoes ou ainda nao estarem especificadas. */

enum tipoentrada_t
{
    ENTR_VAZIA,
    ENTR_VAR,
    ENTR_FUNC
};

/* ================================================================= */
/* FUNCOES DE MANIPULACAO DA TABELA DE SIMBOLOS */
/* ================================================================= */

/* ----------------------------------------------------------------- */
/* FUNCOES RELATIVAS A TABELA DE SIMBOLOS */
/* ----------------------------------------------------------------- */

/* "Setters" a la Java. */
bool tab_atrib_coluna(char *id, int coluna);
bool tab_atrib_linha(char *id, int linha);
bool tab_atrib_tipo(char *id, tipo_t *tipo);
bool tab_atrib_tipo_entr(char *id, int tipo);
bool tab_atrib_valor(char *id, void *valor);
bool tab_declarar(char *id);
bool tab_definir(char *id);
bool tab_inserir_param(char *id, tipo_t *param);

/* "Getters". */
int tab_obter_coluna(char *id);
bool tab_obter_declarada(char *id);
bool tab_obter_definida(char *id);
int tab_obter_linha(char *id);
tipo_t *tab_obter_param(char *id, size_t pos);
size_t tab_obter_qtde_params(char *id, bool *ret);
tipo_t *tab_obter_tipo(char *id);
int tab_obter_tipo_entr(char *id);
void *tab_obter_valor(char *id);

/* Criacao da tabela de simbolos e de entradas na tabela. */
bool tab_criar(void);
bool tab_criar_entr(char *id);

/* Funcoes de proposito geral. */
bool tab_contem(char *id);
void tab_imprimir(void);

/* ----------------------------------------------------------------- */
/* FUNCOES RELATIVAS AOS TIPOS DE DADOS DA LINGUAGEM */
/* ----------------------------------------------------------------- */

/* "Getters. */
tipo_t *tipo_obter(char *nome);
size_t tipo_obter_bytes(tipo_t *tipo);
char *tipo_obter_nome(tipo_t *tipo);
size_t tipos_obter_qtde(void);
tipo_t *tipo_obter_resultante(int oper, tipo_t *tipo1, tipo_t *tipo2);

/* Funcoes de proposito geral. */
void tipo_imprimir(tipo_t *tipo);
void tipo_imprimir_valor(tipo_t *tipo, void *valor);
void tipos_destruir(void);
// bool tipo_validar_atrib (tipo_t *tipo_esq, tipo_t *tipo_dir);

/* ================================================================= */

#endif
