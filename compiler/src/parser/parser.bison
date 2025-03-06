%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "..\src\AST\expr.h"
struct expr * parser_result = 0;

extern char *yytext;  // Declare yytext from Flex

int yylex(void);
int yyerror(char *s);

%}

%union {
	
	char *str;
	struct expr *node;
	int ival;
	float dval;
}

%token <str> TOKEN_ID
%token <ival> TOKEN_INT
%token <dval> TOKEN_DEC
%token TOKEN_PLUS
%token TOKEN_MINUS
%token TOKEN_EQUAL
%token TOKEN_MUL
%token TOKEN_DIV
%token TOKEN_LPAREN
%token TOKEN_RPAREN
%token TOKEN_SEMI
%token TOKEN_ERROR

%type <node> expr
%type <node> expr_list
%type <node> term
%type <node> factor
%type <node> func_call

%%

prog : expr_list { parser_result = $1; }

expr_list : expr TOKEN_SEMI expr_list { $$ = expr_create_list($1, $3); }
		  | expr TOKEN_SEMI { $$ = expr_create_list($1, NULL); }
		  ;

expr : expr TOKEN_PLUS term { $$ = expr_create(EXPR_ADD, $1, $3); }
	 | expr TOKEN_MINUS term { $$ = expr_create(EXPR_SUBTRACT, $1, $3); }
	 | TOKEN_ID TOKEN_EQUAL expr { $$ = expr_create(EXPR_ASSIGN, expr_create_var($1), $3); }
	 | term { $$ = $1; }
	 ;
	 
term : term TOKEN_MUL factor { $$ = expr_create(EXPR_MULTIPLY, $1, $3); }
	 | term TOKEN_DIV factor { $$ = expr_create(EXPR_DIVIDE, $1, $3); }
	 | factor { $$ = $1; }
	 ;

factor : TOKEN_MINUS factor { $$ = expr_create(EXPR_SUBTRACT, expr_create_ival(0), $2); }
	   | TOKEN_LPAREN expr TOKEN_RPAREN { $$ = $2; }
	   | TOKEN_INT { $$ = expr_create_ival($1); }
	   | TOKEN_DEC { $$ = expr_create_dval($1); }
	   | TOKEN_ID { $$ = expr_create_var($1); }
	   | func_call { $$ = $1; }
	   ;

func_call : TOKEN_ID TOKEN_LPAREN expr TOKEN_RPAREN { $$ = expr_create_func($1, $3); }
		  ;
	 
%%
int yyerror( char *s ) {
	printf("parse error: %s\n",s);
	return 1;
}