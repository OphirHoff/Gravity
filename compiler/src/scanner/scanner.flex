%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"
#include "..\src\debug\debug.h"
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
CHAR \'[^\']\'
STRING \"[^\"]*\"
IDENTIFIER [A-Za-z_][A-Za-z0-9_]*

%%

(" "|\t|\n) /* skip whitespace */
{KEYWORD_INT}           { if (DEBUG) printf("TOKEN_INT\n"); return TOKEN_INT; }
{KEYWORD_DEC}           { if (DEBUG) printf("TOKEN_DEC\n"); return TOKEN_DEC; }
{KEYWORD_CHAR}          { if (DEBUG) printf("TOKEN_CHAR\n"); return TOKEN_CHAR; }
{KEYWORD_STR}           { if (DEBUG) printf("TOKEN_STR\n"); return TOKEN_STR; }
{KEYWORD_IF}            { if (DEBUG) printf("TOKEN_IF\n"); return TOKEN_IF; }
{KEYWORD_ELSE}          { if (DEBUG) printf("TOKEN_ELSE\n"); return TOKEN_ELSE; }
{KEYWORD_LOOP}          { if (DEBUG) printf("TOKEN_LOOP\n"); return TOKEN_LOOP; }
{KEYWORD_OUT}           { if (DEBUG) printf("TOKEN_OUT\n"); return TOKEN_OUT; }
{KEYWORD_PROC}          { if (DEBUG) printf("TOKEN_PROC\n"); return TOKEN_PROC; }
{KEYWORD_RET}           { if (DEBUG) printf("TOKEN_RET\n"); return TOKEN_RET; }
\+             			{ if (DEBUG) printf("TOKEN_PLUS\n"); return TOKEN_PLUS; }
\-             			{ if (DEBUG) printf("TOKEN_MINUS\n"); return TOKEN_MINUS; }
\*             			{ if (DEBUG) printf("TOKEN_MUL\n"); return TOKEN_MUL; }
\/             			{ if (DEBUG) printf("TOKEN_DIV\n"); return TOKEN_DIV; }
\=						{ if (DEBUG) printf("TOKEN_EQUAL\n"); return TOKEN_EQUAL; }
"++"                    { if (DEBUG) printf("TOKEN_INCR\n"); return TOKEN_INCR; }
"--"                    { if (DEBUG) printf("TOKEN_DECR\n"); return TOKEN_DECR; }
"<"                     { if (DEBUG) printf("TOKEN_LT\n"); return TOKEN_LT; }
">"                     { if (DEBUG) printf("TOKEN_GT\n"); return TOKEN_GT; }
"$"                     { if (DEBUG) printf("TOKEN_DOLLAR\n"); return TOKEN_DOLLAR; }
"::"                    { if (DEBUG) printf("TOKEN_COLON_COLON\n"); return TOKEN_COLON_COLON; }
\(             			{ if (DEBUG) printf("TOKEN_LPAREN\n"); return TOKEN_LPAREN; }
\)             			{ if (DEBUG) printf("TOKEN_RPAREN\n"); return TOKEN_RPAREN; }
\{                      { if (DEBUG) printf("TOKEN_LBRACE\n"); return TOKEN_LBRACE; }
\}                      { if (DEBUG) printf("TOKEN_RBRACE\n"); return TOKEN_RBRACE; }
\;             			{ if (DEBUG) printf("TOKEN_SEMI\n"); return TOKEN_SEMI; }
\,                      { if (DEBUG) printf("TOKEN_COMMA\n"); return TOKEN_COMMA; }
{DIGIT}+       			{ if (DEBUG) printf("TOKEN_INT_LIT (%s)\n", yytext); yylval.ival = atoi(yytext); return TOKEN_INT_LIT; }
{DIGIT}+\.{DIGIT}+		{ if (DEBUG) printf("TOKEN_DEC_LIT (%s)\n", yytext); yylval.dval = atof(yytext); return TOKEN_DEC_LIT; }
{CHAR}                  { if (DEBUG) printf("TOKEN_CHAR_LIT (%s)\n", yytext); yylval.ch = yytext[1]; return TOKEN_CHAR_LIT; }
{STRING}                { if (DEBUG) printf("TOKEN_STR_LIT (%s)\n", yytext); yylval.str = strdup(yytext); return TOKEN_STR_LIT; }
{IDENTIFIER}              { if (DEBUG) printf("TOKEN_ID (%s)\n", yytext); yylval.str = strdup(yytext); return TOKEN_ID; }
.              			{ if (DEBUG) printf("TOKEN_ERROR: %s\n", yytext); return TOKEN_ERROR; }
%%
int yywrap() { return 1; }