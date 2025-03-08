
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TOKEN_ID = 258,
     TOKEN_INT_LIT = 259,
     TOKEN_DEC_LIT = 260,
     TOKEN_CHAR_LIT = 261,
     TOKEN_STR_LIT = 262,
     TOKEN_INT = 263,
     TOKEN_DEC = 264,
     TOKEN_CHAR = 265,
     TOKEN_STR = 266,
     TOKEN_IF = 267,
     TOKEN_ELSE = 268,
     TOKEN_LOOP = 269,
     TOKEN_PROC = 270,
     TOKEN_OUT = 271,
     TOKEN_RET = 272,
     TOKEN_PLUS = 273,
     TOKEN_MINUS = 274,
     TOKEN_EQUAL = 275,
     TOKEN_MUL = 276,
     TOKEN_DIV = 277,
     TOKEN_INCR = 278,
     TOKEN_DECR = 279,
     TOKEN_LT = 280,
     TOKEN_GT = 281,
     TOKEN_LPAREN = 282,
     TOKEN_RPAREN = 283,
     TOKEN_LBRACE = 284,
     TOKEN_RBRACE = 285,
     TOKEN_COMMA = 286,
     TOKEN_COLON = 287,
     TOKEN_SEMI = 288,
     TOKEN_ERROR = 289
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 18 "src\\parser\\parser.bison"

	struct decl *decl;
	struct stmt *stmt;
	struct expr *expr;
	struct param_list *param;
	struct type *type;
	int ival;
	float dval;
	char ch;
	char *str;

	// struct expr *node;



/* Line 1676 of yacc.c  */
#line 102 "build\\token.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


