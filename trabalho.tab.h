/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_TRABALHO_TAB_H_INCLUDED
# define YY_YY_TRABALHO_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    T_ACOLCH = 258,
    T_APAREN = 259,
    T_ATRIB = 260,
    T_ASPAS_SIMPL = 261,
    T_BRANCO = 262,
    T_BREAK = 263,
    T_BOOL = 264,
    T_CHAR = 265,
    T_FLOAT = 266,
    T_INT = 267,
    T_CONTINUE = 268,
    T_DIFER = 269,
    T_DIV = 270,
    T_DO = 271,
    T_E = 272,
    T_ELSE_FALSO = 273,
    T_ELSE = 274,
    T_ERRO = 275,
    T_FCOLCH = 276,
    T_FOR = 277,
    T_FPAREN = 278,
    T_ID = 279,
    T_IF = 280,
    T_IGUAL = 281,
    T_MAIOR = 282,
    T_MAIOR_IGUAL = 283,
    T_MAIS = 284,
    T_MENOR = 285,
    T_MENOR_IGUAL = 286,
    T_MENOS = 287,
    T_NAO = 288,
    T_NEWLINE = 289,
    T_OU = 290,
    T_OU_EXCL = 291,
    T_PEV = 292,
    T_RESTO = 293,
    T_RETURN = 294,
    T_TIPO = 295,
    T_VEZES = 296,
    T_VIRG = 297,
    T_VOID = 298,
    T_WHILE = 299
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 17 "trabalho.y" /* yacc.c:1909  */

	tipo_t *tipo;		/* Um tipo de dados. */
	char *id;			/* Identificador. */
	int token;			/* O codigo de um token no anal. lexico. */

#line 105 "trabalho.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_TRABALHO_TAB_H_INCLUDED  */
