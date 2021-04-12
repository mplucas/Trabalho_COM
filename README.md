======================================================================
# INFORMACOES BASICAS DO ARQUIVO.
======================================================================

## DESCRICAO: Trabalho de implementação de um compilador. Referente a
disciplina de Compiladores da UDESC-CCT.

###### Alunos: Rafael Boeger e Lucas Meneghelli Pereira

Apresenta a estruturacao dos arquivos que implementam o
compilador de uma linguagem semelhante a C e as caracteristicas dessa
linguagem.
CRIADO EM: 27 mar. 2021.

======================================================================
## REGRAS DA LINGUAGEM
======================================================================

###### Estas sao algumas regras basicas da linguagem:

- Toda funcao deve ser declarada ou definida antes de ser utilizada.
- Toda variavel deve ser definida antes de ser utilizada.
- Nao e possivel apenas declarar uma variavel.
- Toda definicao ou declaracao de funcao sem argumentos deve
	utilizar a palavra-chave void, sozinha, no lugar da lista de
	parametros. Uma chamada de funcao, porem, pode utilizar parenteses
	vazios.
- As condicoes logicas dos comandos condicionais (if) e de repeticao
	(for, while e do-while) devem ser aceitas para que os comandos 	
	associados a essas estruturas sejam executados (óbvio!). O retorno
 	das condicoes logicas deve possuir tipo bool. Retornos de outros
 	tipos (inteiro, p. ex.) constituem um erro semantico.
- A linguagem possui apenas cinco tipos: bool, char, int, float e
	void.
- As unicas conversoes de tipo aceitas sao de int para float e de
	float para int. Essas conversoes sao automaticas.
- Operacoes aritmeticas exigem operandos de tipos aritmeticos.
	Operacoes booleanas exigem operandos booleanos. Operacoes 
	relacionais exigem operandos aritmeticos. As unicas operacoes
	que podem ser realizadas com caracteres sao comparacoes de
	igualdade e diferenca.
- Variaveis podem ser inicializadas ja na sua definicao. Alem disso,
	pode-se usar listas de inicializacao, como int a = 1, b = 2, c;.

======================================================================
# ARQUIVOS
======================================================================

----------------------------------------------------------------------
## ANALISE LEXICA
----------------------------------------------------------------------

- trabalho.lex: arquivo do Flex que implementa o analisador lexico do
	compilador.
	
- lexico.c: a terceira secao de um arquivo do Flex e dedicada as
	funcoes que o programador utiliza para implementar o analisador
	lexico. A fim de evitar tornar muito grande o arquivo trabalho.lex
	as funcoes desenvolvidas para o analisador lexico foram colocadas
	no arquivo lexico.c.
	
- lexico.h: a primeira secao de um arquivo do Flex e dedicada as
	inclusoes e definicoes ou declaracoes de variaveis globais e 
	funcoes. Esses elementos foram colocados no arquivo lexico.h para
	evitar que o arquivo trabalho.lex se tornasse demasiadamente grande.
	
----------------------------------------------------------------------
## ANALISE SINTATICA, ANALISE SEMANTICA E GERACAO DE CODIGO INTERMEDIARIO
----------------------------------------------------------------------

- trabalho.y: arquivo do Bison que implementa o analisador sintatico
	do compilador. Como a tecnica de "traducao dirigida pela sintaxe" e
	utilizada no compilador, esse arquivo tambem especifica as acoes de
	analise semantica e geracao de codigo intermediario que devem ser
	executadas apos o reconhecimento de uma regra de producao.
	
- sintatico.c: a terceira secao de um arquivo do Bison e destinado as
	funcoes que o programador utiliza para implementar as analises
	sintatica e semantica e a geracao de codigo intermediario. Essas
	funcoes foram colocadas no arquivo sintatico.c para evitar que o
	arquivo trabalho.y se tornasse demasiadamente grande.
	
- sintatico.h: a primeira secao de um arquivo do Bison e destinada
	as inclues e declaracoes ou definicoes de variaveis globais e 
	funcoes. Essas declaracoes e funcoes foram colocadas no arquivo
	sintatico.h para evitar tornar o arquivo trabalho.y demasiadamente
	extenso.

----------------------------------------------------------------------
## TABELA DE SIMBOLOS
----------------------------------------------------------------------

- tabsimb.c: contem as funcoes que operam sobre a tabela de simbolos 
	e a variavel que representa a propria tabela de simbolos do
	compilador. 
	A tabela de simbolos foi desenvolvida de modo que o usuario nao 
	precise conhecer sua representacao interna para que possa
	utiliza-la. Basta que ele use as essas funcoes.

- tabsimb.h: contem as assinaturas das funcoes do arquivo tabsimb.c
	e do arquivo tipo.c.

- tabsimb-defs.h: contem as definicoes dos tipos de dados que
	implementam a tabela de simbolos, as entradas da tabela de simbolos
	e os tipos de dados da linguagem.

- entr.c: contem as funcoes que proporcionam as operacoes sobre as
	entradas da tabela de simbolos.

- entr.h: contem as assinaturas das funcoes do arquivo entr.c. Assim
	como a tabela de simbolos, o usuario nao precisa conhecer a
	representa interna de uma entrada da tabela de simbolos para que
	possa operar sobre as entradas. Basta que ele utilize essas
	funcoes.

- tipo.c: a implementacao do compilador define um tipo de dados que
	representa os tipos de dados da linguagem. O objetivo dessa escolha
	e permitir que todas as referencias ao tipos de dados da linguagem
	se refiram ao mesmo objeto. O arquivo tipo.c contem as funcoes que
	manipulam esse tipo de dados.

----------------------------------------------------------------------
## ESTRUTURAS DE DADOS GENERICAS
----------------------------------------------------------------------

- lista.c: contem as funcoes que operam sobre uma lista simplesmente
	encadeda.

- lista.h: contem as assinaturas das funcoes do arquivo lista.c

- lista-defs.h: contem as definicoes dos tipos de dados que
	implementa a lista simplesmente encadeada.

----------------------------------------------------------------------
## OUTROS ARQUIVOS
----------------------------------------------------------------------

- script: e o arquivo que deve ser executado no terminal para gerar
	o arquivo a.out, que executa o compilador. 

- arquivo.txt: um arquivo com um trecho de codigo da linguagem correto
	dos pontos de vista lexico e sintatico, mas nao semantico.

======================================================================
## ACOES DE ANALISE SEMANTICA
======================================================================

Nem todas as acoes de analise semantica necessarias para o
funcionamento completo do compilador foram implementadas. As seguintes
verificacoes de analise semantica estao em funcionamento:

-- se um identificador foi declarado antes do seu uso.
-- se o tipo do identificador (funcao ou variavel) e compativel com seu
uso. Por exemplo: o compilador indica erro se um identificador
relativo a uma variavel e usado numa chamada de funcao.
-- se o valor de inicializacao de uma variavel em sua declaracao e
compativel com o tipo indicado para a variavel.
-- se os tipos dos operandos em expressoes estao corretos.
-- se uma variavel esta sendo redeclarada.

## Passo a passo para testar
---------------------------------------------------------------------
- Alterar o arquivo compile_script para executável e executar:
make compile_script

- Esse comando irá gerar o a.out, que é o compilador, após isso,
executar:
./a.out test.txt
- test.txt é um exemplo de arquivo a ser lido pelo compilador que
contem os testes pedidos

- Após isso, o java_bytecode.j é gerado. Executar o comando:
make bytecode_to_jasmin_and_execute

- Se quiser fazer todos os passos juntos, executar apenas:
make full_test
- Isso, sendo que o codigo a ser compilado se encontra em test.txt

## Funcionalidades completadas
---------------------------------------------------------------------
- Atribuições de variáveis
- Prints de cada tipo
    - print_int()
    - print_float()
    - print_char()
    - print_bool()
- Operações aritméticas: +, -, *, /, %
- Operações booleanas: &&, ||
- Comando If, bem como comparação de valores dentro de Ifs:
    - if(x < y), if(x <= y), if(x > y), if(x >= y), if(x == y), if(x != y)
- Laço de repetição while, com as mesmas comparações do if:
    - while(x < y), while(x <= y), while(x > y), while(x >= y), while(x == y), while(x != y)