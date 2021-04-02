# include <stdlib.h>
# include "tabsimb-defs.h"

/* ================================================================= */
/* INFORMACOES BASICAS DO ARQUIVO */
/* ================================================================= */

/* DESCRICAO: contem as assinaturas das funcoes que manipulam uma
 * entrada da tabela de simbolos. */
/* CRIADO EM: 27 mar. 2021. */

/* ================================================================= */
/* FUNCOES DE MANIPULACAO DE ENTRADAS DA TABELA DE SIMBOLOS */
/* ================================================================= */

bool entr_atrib_coluna (entr_t *entr, int coluna);
bool entr_atrib_linha (entr_t *entr, int linha);
bool entr_atrib_tipo (entr_t *entr, tipo_t *tipo);
bool entr_atrib_tipo_entr (entr_t *entr, int tipo);
bool entr_atrib_valor (entr_t *entr, void *valor);
entr_t *entr_criar (char *id);
void entr_imprimir (entr_t *entr);
bool entr_inserir_param (entr_t *entr, tipo_t **param);
void entr_marcar_como_declarada (entr_t *entr);
void entr_marcar_como_definida (entr_t *entr);
int entr_obter_coluna (entr_t *entr);
bool entr_obter_declarada (entr_t *entr);
bool entr_obter_definida (entr_t *entr);
int entr_obter_linha (entr_t *entr);
tipo_t *entr_obter_param (entr_t *entr, size_t pos);
size_t entr_obter_qtde_params (entr_t *entr);
tipo_t *entr_obter_tipo (entr_t *entr);
int entr_obter_tipo_entr (entr_t *entr);
void *entr_obter_valor (entr_t *entr);

