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
%token <ival> TOKEN_INT_LIT
%token <dval> TOKEN_DEC_LIT
%token TOKEN_IF
%token TOKEN_ELSE
%token TOKEN_LOOP
%token TOKEN_OUT
%token TOKEN_RET
%token TOKEN_PLUS
%token TOKEN_MINUS
%token TOKEN_EQUAL
%token TOKEN_MUL
%token TOKEN_DIV
%token TOKEN_LPAREN
%token TOKEN_RPAREN
%token TOKEN_LBRACE
%token TOKEN_RBRACE
%token TOKEN_COLON
%token TOKEN_SEMI
%token TOKEN_ERROR

%type <node> expr
%type <node> expr_list
%type <node> term
%type <node> factor
%type <node> func_call

%%

prog : decl_list { parser_result =  $1; }

decl_list : decl decl_list { $$ = $1; $1->next = $2; }
		  | /* epsilon */
		  { $$ = 0; }
		  ;

decl : type name TOKEN_SEMI { $$ = decl_create($2, $1, 0, 0, 0); }
	 | type name TOKEN_EQUAL expr TOKEN_SEMI { $$ = decl_create($2, $1, $4, 0, 0); }
	 /* more cases here */
	 ;

stmt : decl { $$ = stmt_create(STMT_DECL, $1, 0, 0, 0, 0, 0, 0); }
	 | expr { $$ = $1 }
	 | TOKEN_IF TOKEN_LPAREN expr TOKEN_RPAREN stmt { $$ = stmt_create(STMT_IF_ELSE, 0, 0, $3, 0, $5, 0, 0); }
	 | TOKEN_LOOP TOKEN_LPAREN expr TOKEN_SEMI expr TOKEN_SEMI expr TOKEN_RPAREN stmt { $$ = stmt_create(STMT_FOR, 0, $3, $5, $7, $9); }
	 | TOKEN_OUT TOKEN_LPAREN expr TOKEN_RPAREN TOKEN_SEMI { $$ = stmt_create(STMT_PRINT, 0, 0, $3, 0, 0, 0, 0); }
	 | TOKEN_RET expr TOKEN_SEMI { $$ = stmt_create(STMT_RETURN, 0, 0, $3, 0, 0, 0, 0); }
	 | TOKEN_LBRACE stmt_list TOKEN_RBRACE
	 ;

expr : expr TOKEN_PLUS term { $$ = expr_create(EXPR_ADD, $1, $3); }
	 | expr TOKEN_MINUS term { $$ = expr_create(EXPR_SUBTRACT, $1, $3); }
	 | TOKEN_ID TOKEN_EQUAL expr { $$ = expr_create(EXPR_ASSIGN, expr_create_var($1), $3); }
	 | term { $$ = $1; }
	 ;


/* prog : expr_list { parser_result = $1; }

expr_list : expr TOKEN_SEMI expr_list { $$ = expr_create_list($1, $3); }
		  | expr TOKEN_SEMI { $$ = expr_create_list($1, NULL); }
		  ;

decl : name TOKEN_COLON type TOKEN_SEMI

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
		  ; */
	 
%%
int yyerror( char *s ) {
	printf("parse error: %s\n",s);
	return 1;
}