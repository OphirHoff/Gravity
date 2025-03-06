#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "expr.h"

struct expr * expr_create ( expr_t kind, 
							struct expr *left,
							struct expr *right )
{
	struct expr *e = malloc(sizeof(*e));
	e->kind = kind;
	e->value = 0;
	e->left = left;
	e->right = right;
	e->var_name = strdup("");
	e->list = 0;
	
	return e;
}

struct expr * expr_create_dval ( float value ) {
	
	struct expr *e = expr_create(EXPR_VALUE, 0, 0);
	e->value = value;
	return e;
}

struct expr *expr_create_ival(int value) {
	
	struct expr *e = expr_create(EXPR_VALUE, 0, 0);
	e->value = (float)value;
	return e;
}

struct expr *expr_create_var(char *name) {
	
	struct expr *e = expr_create(EXPR_VAR, 0, 0);
	e->var_name = strdup(name);
	return e;
}

struct expr *expr_create_func(char *name, struct expr *arg) {
	
	struct expr *e = expr_create(EXPR_FUNCTION, 0, 0);
	e->var_name = strdup(name);
	e->left = arg;
	return e;
}

struct expr *expr_create_list(struct expr *exp, struct expr * next_exp) {
	struct expr *e = expr_create(EXPR_LIST, 0, 0);
	e->left = exp;
	e->right = next_exp;
	return e;
}