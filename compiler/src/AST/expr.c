#include "expr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct expr *expr_create(expr_t kind, struct expr *left, struct expr *right) {

  struct expr *e = malloc(sizeof(*e));
  e->kind = kind;
  e->left = left;
  e->right = right;

  e->var_name = NULL;
  e->int_value = 0;
  e->float_value = 0;
  e->str_literal = NULL;

  return e;
}

struct expr *expr_create_int_literal(int value) {

  struct expr *e = expr_create(EXPR_INT_LITERAL, 0, 0);
  e->int_value = value;
  return e;
}

struct expr *expr_create_float_literal(float value) {

  struct expr *e = expr_create(EXPR_FLOAT_LITERAL, 0, 0);
  e->float_value = value;
  return e;
}

struct expr *expr_create_char_literal(char ch) {

  struct expr *e = expr_create(EXPR_CHAR_LITERAL, 0, 0);
  e->int_value = ch;
  return e;
}

struct expr *expr_create_string_literal(const char *str) {

  struct expr *e = expr_create(EXPR_STR_LITERAL, 0, 0);
  e->str_literal = str;
  return e;
}

struct expr *expr_create_var(const char *name) {

  struct expr *e = expr_create(EXPR_VAR, 0, 0);
  e->var_name = strdup(name);
  return e;
}
