%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"
#include "..\src\AST\expr.h"

%}

DIGIT [0-9]
LETTER [a-zA-Z]
STRING \"[^\"]*\"

%%

(" "|\t|\n) /* skip whitespace */
\+             			{ printf("TOKEN_PLUS\n"); return TOKEN_PLUS; }
\-             			{ printf("TOKEN_MINUS\n"); return TOKEN_MINUS; }
\*             			{ printf("TOKEN_MUL\n"); return TOKEN_MUL; }
\/             			{ printf("TOKEN_DIV\n"); return TOKEN_DIV; }
\=						{ printf("TOKEN_EQUAL\n"); return TOKEN_EQUAL; }
\(             			{ printf("TOKEN_LPAREN\n"); return TOKEN_LPAREN; }
\)             			{ printf("TOKEN_RPAREN\n"); return TOKEN_RPAREN; }
\;             			{ printf("TOKEN_SEMI\n"); return TOKEN_SEMI; }
{DIGIT}+       			{ printf("TOKEN_INT (%s)\n", yytext); yylval.ival = atoi(yytext); return TOKEN_INT; }
{DIGIT}+\.{DIGIT}+		{ printf("TOKEN_DEC (%s)\n", yytext); yylval.dval = atof(yytext); return TOKEN_DEC; }
_*{LETTER}+{DIGIT}*_*	{ printf("TOKEN_ID (%s)\n", yytext); yylval.str = strdup(yytext); return TOKEN_ID; }
.              			{ printf("TOKEN_ERROR: %s\n", yytext); return TOKEN_ERROR; }
%%
int yywrap() { return 1; }