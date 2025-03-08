%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"
#include "..\src\AST\expr.h"
%}

KEYWORD_INT   "int"
KEYWORD_DEC   "dec"
KEYWORD_CHAR  "char"
KEYWORD_STR   "str"
KEYWORD_IF    "if"
KEYWORD_ELSE  "else"
KEYWORD_LOOP  "loop"
KEYWORD_OUT   "out"
KEYWORD_PROC  "proc"
KEYWORD_RET   "ret"

DIGIT [0-9]
LETTER [a-zA-Z]
CHAR \'[^\']\'
STRING \"[^\"]*\"

%%

(" "|\t|\n) /* skip whitespace */
{KEYWORD_INT}           { printf("TOKEN_INT\n"); return TOKEN_INT; }
{KEYWORD_DEC}           { printf("TOKEN_DEC\n"); return TOKEN_DEC; }
{KEYWORD_CHAR}          { printf("TOKEN_CHAR\n"); return TOKEN_CHAR; }
{KEYWORD_STR}           { printf("TOKEN_STR\n"); return TOKEN_STR; }
{KEYWORD_IF}            { printf("TOKEN_IF\n"); return TOKEN_IF; }
{KEYWORD_ELSE}          { printf("TOKEN_ELSE\n"); return TOKEN_ELSE; }
{KEYWORD_LOOP}          { printf("TOKEN_LOOP\n"); return TOKEN_LOOP; }
{KEYWORD_OUT}           { printf("TOKEN_OUT\n"); return TOKEN_OUT; }
{KEYWORD_PROC}          { printf("TOKEN_PROC\n"); return TOKEN_PROC; }
{KEYWORD_RET}           { printf("TOKEN_RET\n"); return TOKEN_RET; }
\+             			{ printf("TOKEN_PLUS\n"); return TOKEN_PLUS; }
\-             			{ printf("TOKEN_MINUS\n"); return TOKEN_MINUS; }
\*             			{ printf("TOKEN_MUL\n"); return TOKEN_MUL; }
\/             			{ printf("TOKEN_DIV\n"); return TOKEN_DIV; }
\=						{ printf("TOKEN_EQUAL\n"); return TOKEN_EQUAL; }
"++"                    { printf("TOKEN_INCR\n"); return TOKEN_INCR; }
"--"                    { printf("TOKEN_DECR\n"); return TOKEN_DECR; }
"<"                     { printf("TOKEN_LT\n"); return TOKEN_LT; }
">"                     { printf("TOKEN_GT\n"); return TOKEN_GT; }
\(             			{ printf("TOKEN_LPAREN\n"); return TOKEN_LPAREN; }
\)             			{ printf("TOKEN_RPAREN\n"); return TOKEN_RPAREN; }
\{                      { printf("TOKEN_LBRACE\n"); return TOKEN_LBRACE; }
\}                      { printf("TOKEN_RBRACE\n"); return TOKEN_RBRACE; }
\;             			{ printf("TOKEN_SEMI\n"); return TOKEN_SEMI; }
\,                      { printf("TOKEN_COMMA\n"); return TOKEN_COMMA; }
{DIGIT}+       			{ printf("TOKEN_INT_LIT (%s)\n", yytext); yylval.ival = atoi(yytext); return TOKEN_INT_LIT; }
{DIGIT}+\.{DIGIT}+		{ printf("TOKEN_DEC_LIT (%s)\n", yytext); yylval.dval = atof(yytext); return TOKEN_DEC_LIT; }
{CHAR}                  { printf("TOKEN_CHAR_LIT (%s)\n", yytext);
                            char *s = strdup(yytext); yylval.ch = *s; free(s); return TOKEN_CHAR_LIT; }
{STRING}                { printf("TOKEN_STR_LIT (%s)\n", yytext); yylval.str = strdup(yytext); return TOKEN_STR_LIT; }
_*{LETTER}+{DIGIT}*_*	{ printf("TOKEN_ID (%s)\n", yytext); yylval.str = strdup(yytext); return TOKEN_ID; }
.              			{ printf("TOKEN_ERROR: %s\n", yytext); return TOKEN_ERROR; }
%%
int yywrap() { return 1; }