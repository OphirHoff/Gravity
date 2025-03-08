%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "..\src\AST\decl.h"
#include "..\src\AST\stmt.h"
#include "..\src\AST\expr.h"

struct decl *parser_result = 0;

extern char *yytext;  // Declare yytext from Flex

int yylex(void);
int yyerror(char *s);

%}

%union {
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
}

%token <str> TOKEN_ID
%token <ival> TOKEN_INT_LIT
%token <dval> TOKEN_DEC_LIT
%token <ch> TOKEN_CHAR_LIT
%token <str> TOKEN_STR_LIT
%token TOKEN_INT
%token TOKEN_DEC
%token TOKEN_CHAR
%token TOKEN_STR
%token TOKEN_IF
%token TOKEN_ELSE
%token TOKEN_LOOP
%token TOKEN_PROC
%token TOKEN_OUT
%token TOKEN_RET
%token TOKEN_PLUS
%token TOKEN_MINUS
%token TOKEN_EQUAL
%token TOKEN_MUL
%token TOKEN_DIV
%token TOKEN_INCR
%token TOKEN_DECR
%token TOKEN_LT
%token TOKEN_GT
%token TOKEN_LPAREN
%token TOKEN_RPAREN
%token TOKEN_LBRACE
%token TOKEN_RBRACE
%token TOKEN_COMMA
%token TOKEN_SEMI
%token TOKEN_ERROR

%type <decl> prog decl_list decl
%type <stmt> stmt_list stmt
%type <expr> expr
%type <param> param_list param
%type <type> type

/* Set Precedence */
%right TOKEN_EQUAL
%left TOKEN_PLUS TOKEN_MINUS
%left TOKEN_MUL TOKEN_DIV
%left TOKEN_LT TOKEN_GT
%right TOKEN_INCR TOKEN_DECR
%right "then" TOKEN_ELSE

%%

prog : decl_list { parser_result =  $1; } ;

decl_list : decl decl_list { $$ = $1; $1->next = $2; }
		  | /* epsilon */
		  	{ $$ = 0; }
		  ;

decl : type TOKEN_ID TOKEN_SEMI { $$ = decl_create($2, $1, 0, 0, 0); }
	 | type TOKEN_ID TOKEN_EQUAL expr TOKEN_SEMI { $$ = decl_create($2, $1, $4, 0, 0); } 				 // Variables
	 | TOKEN_PROC type TOKEN_ID TOKEN_LPAREN param_list TOKEN_RPAREN TOKEN_LBRACE stmt_list TOKEN_RBRACE // Functions
	 	{ $$ = decl_create($3, type_create(TYPE_FUNCTION, $2, $5), 0, $8, 0); }
	 ;

stmt_list : stmt stmt_list { $$ = $1; $1->next = $2; }
		  | /* epsilon */
		  	{ $$ = 0; }
		  ;

stmt : decl { $$ = stmt_create(STMT_DECL, $1, 0, 0, 0, 0, 0, 0); }
	 | expr TOKEN_SEMI { $$ = stmt_create(STMT_EXPR, 0, 0, $1, 0, 0, 0, 0); }
	 | TOKEN_IF TOKEN_LPAREN expr TOKEN_RPAREN stmt { $$ = stmt_create(STMT_IF_ELSE, 0, 0, $3, 0, $5, 0, 0); } %prec "then" // Solve conflict
	 | TOKEN_IF TOKEN_LPAREN expr TOKEN_RPAREN stmt TOKEN_ELSE stmt { $$ = stmt_create(STMT_IF_ELSE, 0, 0, $3, 0, $5, $7, 0); }
	 | TOKEN_LOOP TOKEN_LPAREN expr TOKEN_SEMI expr TOKEN_SEMI expr TOKEN_RPAREN stmt { $$ = stmt_create(STMT_FOR, 0, $3, $5, $7, $9, 0, 0); }
	 | TOKEN_OUT TOKEN_LPAREN expr TOKEN_RPAREN TOKEN_SEMI { $$ = stmt_create(STMT_PRINT, 0, 0, $3, 0, 0, 0, 0); }
	 | TOKEN_RET expr TOKEN_SEMI { $$ = stmt_create(STMT_RETURN, 0, 0, $2, 0, 0, 0, 0); }
	 | TOKEN_LBRACE stmt_list TOKEN_RBRACE { $$ = stmt_create(STMT_BLOCK, 0, 0, 0, 0, $2, 0, 0); }
	 ;

expr : expr TOKEN_PLUS expr { $$ = expr_create(EXPR_ADD, $1, $3); }
	 | expr TOKEN_MINUS expr { $$ = expr_create(EXPR_SUB, $1, $3); }
	 | expr TOKEN_MUL expr { $$ = expr_create(EXPR_MUL, $1, $3); }
	 | expr TOKEN_DIV expr { $$ = expr_create(EXPR_DIV, $1, $3); }
	 | expr TOKEN_LT expr { $$ = expr_create(EXPR_LT, $1, $3); }
	 | expr TOKEN_GT expr { $$ = expr_create(EXPR_GT, $1, $3); }
	 | expr TOKEN_INCR { $$ = expr_create(EXPR_INC, $1, 0); }
	 | expr TOKEN_DECR { $$ = expr_create(EXPR_DEC, $1, 0); }
	 | TOKEN_INT_LIT { $$ = expr_create_int_literal($1); }
	 | TOKEN_DEC_LIT { $$ = expr_create_float_literal($1); }
	 | TOKEN_CHAR_LIT { $$ = expr_create_char_literal($1); }
	 | TOKEN_STR_LIT { $$ = expr_create_string_literal($1); }
	 | TOKEN_MINUS expr { $$ = expr_create(EXPR_SUB, expr_create_int_literal(0), $2); }
	 | TOKEN_ID { $$ = expr_create_var($1); }
	 | TOKEN_ID TOKEN_EQUAL expr { $$ = expr_create(EXPR_ASSIGN, expr_create_var($1), $3); }
	 | TOKEN_LPAREN expr TOKEN_RPAREN { $$ = $2; }
	 ;

param_list : param { $$ = $1; }
		   | param TOKEN_COMMA param_list { $$ = $1; $1->next = $3; }
		   | /* epsilon */
		 	{ $$ = 0; }
		   ;

param : type TOKEN_ID { $$ = param_create($2, $1, 0); }
	  ;

type : TOKEN_INT { $$ = type_create(TYPE_INTEGER, 0, 0); }
	 | TOKEN_DEC { $$ = type_create(TYPE_DECIMAL, 0, 0); }
	 | TOKEN_CHAR { $$ = type_create(TYPE_CHARACTER, 0, 0); }
	 | TOKEN_STR { $$ = type_create(TYPE_STRING, 0, 0); }
	 ;
	 
%%
int yyerror( char *s ) {
	printf("parse error: %s\n",s);
	return 1;
}