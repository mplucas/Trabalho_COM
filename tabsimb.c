#include "entr.h"
#include <stdio.h>
#include <string.h>
#include "tabsimb-defs.h"
#include "tabsimb.h"

/* ================================================================= */
/* INFORMACOES BASICAS DO ARQUIVO */
/* ================================================================= */

/* DESCRICAO: contem as funcoes relativas as operacoes sobre a tabela
   de simbolos. */
/* CRIADO EM: 19 mar. 2021. */

/* ================================================================= */
/* ASSINATURAS DE FUNCOES ESTATICAS. */
/* ================================================================= */

static entr_t *tab_buscar(char *id, size_t *pos);

/* ================================================================= */
/* MAIN (usado para fins de teste) */
/* ================================================================= */

tabsimb_t *tab = NULL;

// # define TESTE_TABSIMB

#ifdef TESTE_TABSIMB

int main(void)
{
    printf("tab_criar(): %d\n", tab_criar());

    /* Teste com uma entrada de variavel. */

    char *id_var = "var_de_teste";
    tab_criar_entr(id_var);
    tab_atrib_tipo_entr(id_var, ENTR_VAR);
    tab_atrib_tipo(id_var, tipo_obter("float"));
    float fval = 10.67;
    tab_atrib_valor(id_var, &fval);
    tab_atrib_linha(id_var, 1);
    tab_atrib_coluna(id_var, 12);

    /* Teste com uma entrada de funcao. */

    char *id_func = "funcao_de_teste";
    tab_criar_entr(id_func);
    tab_atrib_tipo_entr(id_func, ENTR_FUNC);
    tab_atrib_tipo(id_func, tipo_obter("char"));
    char cval = 'R';
    tab_atrib_valor(id_func, &cval);
    tab_definir_func(id_func);
    tab_inserir_param(id_func, tipo_obter("int"));
    tab_inserir_param(id_func, tipo_obter("int"));
    tab_inserir_param(id_func, tipo_obter("int"));
    tab_atrib_linha(id_func, 8);
    tab_atrib_coluna(id_func, 13);

    tab_imprimir();

    return (0);
}

#endif

/* ================================================================= */
/* FUNCOES */
/* ================================================================= */

/* ----------------------------------------------------------------- */
/* ATRIBUIR COLUNA A UMA ENTRADA */
/* ----------------------------------------------------------------- */

bool tab_atrib_coluna(char *id, int coluna)
{
    /* Verificando se a tabela de simbolos esta alocada. */
    if (tab == NULL)
    {
        return (false);
    }

    /* Busca da entrada cujo id e igual ao do argumento. */
    size_t pos;
    entr_t *entr = tab_buscar(id, &pos);
    if (entr == NULL)
    {
        return (false);
    }

    /* Atribuicao da coluna a entrada. */
    if (entr_atrib_coluna(entr, coluna) == false)
    {
        return (false);
    }
    lista_alterar(tab->entrs, pos, entr, NULL);
    return (false);
}

/* ----------------------------------------------------------------- */
/* ATRIBUIR LINHA A UMA ENTRADA */
/* ----------------------------------------------------------------- */

bool tab_atrib_linha(char *id, int linha)
{
    /* Verificando se a tabela de simbolos esta alocada. */
    if (tab == NULL)
    {
        return (false);
    }

    /* Busca da entrada cujo id e igual ao do argumento. */
    size_t pos;
    entr_t *entr = tab_buscar(id, &pos);
    if (entr == NULL)
    {
        return (false);
    }

    /* Atribuicao da coluna a entrada. */
    if (entr_atrib_linha(entr, linha) == false)
    {
        return (false);
    }
    lista_alterar(tab->entrs, pos, entr, NULL);
    return (true);
}

/* ----------------------------------------------------------------- */
/* ATRIBUIR TIPO DE DADOS A UMA ENTRADA */
/* ----------------------------------------------------------------- */

bool tab_atrib_tipo(char *id, tipo_t *tipo)
{
    /* Verificando se a tabela de simbolos esta alocada. */
    if (tab == NULL)
    {
        return (false);
    }

    /* Busca da entrada cujo id e igual ao do argumento. */
    size_t pos;
    entr_t *entr = tab_buscar(id, &pos);
    if (entr == NULL)
    {
        return (false);
    }

    /* Atribuicao da coluna a entrada. */
    if (entr_atrib_tipo(entr, tipo) == false)
    {
        return (false);
    }
    lista_alterar(tab->entrs, pos, entr, NULL);
    return (true);
}

/* ----------------------------------------------------------------- */
/* ATRIBUIR TIPO DE ENTRADA DE UMA ENTRADA */
/* ----------------------------------------------------------------- */

bool tab_atrib_tipo_entr(char *id, int tipo)
{
    /* Busca da entrada cujo id e o fornecido como argumento. */
    size_t pos;
    entr_t *entr = tab_buscar(id, &pos);
    if (entr == NULL)
    {
        return (false);
    }

    /* Atribuicao do tipo da entrada. */
    if (entr_atrib_tipo_entr(entr, tipo) == false)
    {
        return (false);
    }
    lista_alterar(tab->entrs, pos, entr, NULL);
    return (true);
}

/* ----------------------------------------------------------------- */
/* ATRIBUIR VALOR A UMA ENTRADA */
/* ----------------------------------------------------------------- */

bool tab_atrib_valor(char *id, void *valor)
{
    /* Verificando se a tabela de simbolos esta alocada. */
    if (tab == NULL)
    {
        return (false);
    }

    /* Busca da entrada cujo id e igual ao do argumento. */
    size_t pos;
    entr_t *entr = tab_buscar(id, &pos);
    if (entr == NULL)
    {
        return (false);
    }

    /* Atribuicao da coluna a entrada. */
    if (entr_atrib_valor(entr, valor) == false)
    {
        return (false);
    }
    lista_alterar(tab->entrs, pos, entr, NULL);
    return (true);
}

/* ----------------------------------------------------------------- */
/* BUSCAR ENTRADA NA TABELA */
/* ----------------------------------------------------------------- */

static entr_t *tab_buscar(char *id, size_t *pos)
{
    /* Verificacao do estado da tabela. */
    if (tab == NULL)
    {
        return (NULL);
    }

    /* Alocacao da entrada. */
    entr_t *entr = malloc(sizeof(entr_t));
    if (entr == NULL)
    {
        return (NULL);
    }

    /* Busca da entrada cujo id e igual ao argumento. */
    for (size_t i = 0; i < lista_tamanho(tab->entrs, NULL); i++)
    {
        lista_buscar(tab->entrs, i, entr);
        if (strcmp(id, entr->id) == 0)
        {
            if (pos != NULL)
            {
                *pos = i;
            }
            return (entr);
        }
    }
    free(entr);
    return (NULL);
}

/* ----------------------------------------------------------------- */
/* VERIFICAR SE UMA ENTRADA ESTA NA TABELA */
/* ----------------------------------------------------------------- */

bool tab_contem(char *id)
{
    entr_t *entr = tab_buscar(id, NULL);
    return ((entr != NULL) ? true : false);
}

/* ----------------------------------------------------------------- */
/* CRIAR TABELA DE SIMBOLOS */
/* ----------------------------------------------------------------- */

bool tab_criar(void)
{
    /* Alocacao da tabela de simbolos. */
    if (tab == NULL)
    {
        tab = malloc(sizeof(tabsimb_t));
        if (tab == NULL)
        {
            return (false);
        }
    }

    /* Alocacao da lista entradas da tabela de simbolos. */
    tab->entrs = lista_criar(sizeof(entr_t));
    if (tab->entrs == NULL)
    {
        free(tab);
        tab = NULL;
        return (false);
    }

    return (true);
}

/* ----------------------------------------------------------------- */
/* CRIAR ENTRADA NA TABELA */
/* ----------------------------------------------------------------- */

bool tab_criar_entr(char *id)
{
    if (tab == NULL)
    {
        return (false);
    }

    /* Verificacao da existencia de uma entrada com o id fornecido. */
    size_t pos;
    entr_t *entr = tab_buscar(id, &pos);
    if (entr != NULL)
    {
        return (false);
    }

    /* Criacao da entrada */
    entr = entr_criar(id);
    if (entr == NULL)
    {
        return (false);
    }

    /* Insercao da entrada na tabela de simbolos. */
    return (lista_anexar(tab->entrs, entr));
}

/* ----------------------------------------------------------------- */
/* MARCAR UMA ENTRADA COMO DECLARADA */
/* ----------------------------------------------------------------- */

bool tab_declarar(char *id)
{
    /* Verificacao do estado de alocacao da tabela de simbolos. */
    if (tab == NULL)
    {
        return (false);
    }

    /* Busca da entrada correspondente ao id fornecido. */
    size_t pos;
    entr_t *entr = tab_buscar(id, &pos);
    if (entr == NULL)
    {
        return (false);
    }

    /* Marcacao da funcao como definida. */
    entr_marcar_como_declarada(entr);
    lista_alterar(tab->entrs, pos, entr, NULL);
    return (true);
}

/* ----------------------------------------------------------------- */
/* MARCAR UMA ENTRADA COMO DEFINIDA */
/* ----------------------------------------------------------------- */

bool tab_definir(char *id)
{
    /* Verificacao do estado de alocacao da tabela de simbolos. */
    if (tab == NULL)
    {
        return (false);
    }

    /* Busca da entrada correspondente ao id fornecido. */
    size_t pos;
    entr_t *entr = tab_buscar(id, &pos);
    if (entr == NULL)
    {
        return (false);
    }

    /* Marcacao da funcao como definida. */
    entr_marcar_como_definida(entr);
    lista_alterar(tab->entrs, pos, entr, NULL);
    return (true);
}

/* ----------------------------------------------------------------- */
/* IMPRIMIR TABELA DE SIMBOLOS */
/* ----------------------------------------------------------------- */

void tab_imprimir(void)
{
    lista_detalhar(tab->entrs, (void (*)(void *))entr_imprimir, "\n");
}

/* ----------------------------------------------------------------- */
/* INSERIR PARAMETRO A UMA ENTRADA */
/* ----------------------------------------------------------------- */

bool tab_inserir_param(char *id, tipo_t *param)
{
    /* Verificacao do estado de alocacao da tabela. */
    if (tab == NULL)
    {
        return (false);
    }

    /* Busca pela entrada correspondente ao id fornecido. */
    size_t pos;
    entr_t *entr = tab_buscar(id, &pos);
    if (entr == NULL)
    {
        return (false);
    }

    /* Insercao do parametro na entrada. */
    if (entr_inserir_param(entr, &param) == false)
    {
        return (false);
    }
    lista_alterar(tab->entrs, pos, entr, NULL);
    return (true);
}

/* ----------------------------------------------------------------- */
/* OBTER COLUNA DE UMA ENTRADA. */
/* ----------------------------------------------------------------- */

int tab_obter_coluna(char *id)
{
    entr_t *entr = tab_buscar(id, NULL);
    if (entr == NULL)
    {
        return (-1);
    }

    return (entr_obter_coluna(entr));
}

/* ----------------------------------------------------------------- */
/* OBTER FLAG DE DECLARACAO DE UMA ENTRADA. */
/* ----------------------------------------------------------------- */

bool tab_obter_declarada(char *id)
{
    entr_t *entr = tab_buscar(id, NULL);
    if (entr == NULL)
    {
        return (false);
    }

    return (entr_obter_declarada(entr));
}

/* ----------------------------------------------------------------- */
/* OBTER FLAG DE DEFINICAO DE UMA ENTRADA. */
/* ----------------------------------------------------------------- */

bool tab_obter_definida(char *id)
{
    entr_t *entr = tab_buscar(id, NULL);
    if (entr == NULL)
    {
        return (false);
    }

    return (entr_obter_definida(entr));
}

/* ----------------------------------------------------------------- */
/* OBTER LINHA DE UMA ENTRADA. */
/* ----------------------------------------------------------------- */

int tab_obter_linha(char *id)
{
    entr_t *entr = tab_buscar(id, NULL);
    if (entr == NULL)
    {
        return (-1);
    }

    return (entr_obter_linha(entr));
}

/* ----------------------------------------------------------------- */
/* OBTER PARAMETRO DE UMA ENTRADA. */
/* ----------------------------------------------------------------- */

tipo_t *tab_obter_param(char *id, size_t pos)
{
    entr_t *entr = tab_buscar(id, NULL);
    if (entr == NULL)
    {
        return (NULL);
    }

    return (entr_obter_param(entr, pos));
}

/* ----------------------------------------------------------------- */
/* OBTER QUANTIDADE DE PARAMETROS DE UMA ENTRADA DE FUNCAO. */
/* ----------------------------------------------------------------- */

size_t tab_obter_qtde_params(char *id, bool *ret)
{
    /* ret e uma flag opcional, util para verificar se o valor retornado 
		pela funcao esta correto ou apenas indica que a entrada
		procurada nao existe. */
    entr_t *entr = tab_buscar(id, NULL);
    if (entr == NULL)
    {
        if (ret != NULL)
        {
            *ret = false;
        }
        return (0);
    }

    if (ret != NULL)
    {
        *ret = true;
    }
    return (entr_obter_qtde_params(entr));
}

/* ----------------------------------------------------------------- */
/* OBTER TIPO DE DADOS DE UMA ENTRADA. */
/* ----------------------------------------------------------------- */

tipo_t *tab_obter_tipo(char *id)
{
    entr_t *entr = tab_buscar(id, NULL);
    if (entr == NULL)
    {
        return (NULL);
    }

    return (entr_obter_tipo(entr));
}

/* ----------------------------------------------------------------- */
/* OBTER TIPO DE ENTRADA. */
/* ----------------------------------------------------------------- */

int tab_obter_tipo_entr(char *id)
{
    entr_t *entr = tab_buscar(id, NULL);
    if (entr == NULL)
    {
        return (-1);
    }

    return (entr_obter_tipo_entr(entr));
}

/* ----------------------------------------------------------------- */
/* OBTER VALOR DE UMA ENTRADA. */
/* ----------------------------------------------------------------- */

void *tab_obter_valor(char *id)
{
    entr_t *entr = tab_buscar(id, NULL);
    if (entr == NULL)
    {
        return (NULL);
    }

    return (entr_obter_valor(entr));
}
