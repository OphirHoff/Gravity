#ifndef EXPR_H
#define EXPR_H

typedef enum {
  EXPR_ADD,
  EXPR_SUB,
  EXPR_MUL,
  EXPR_DIV,
  EXPR_INC,
  EXPR_DEC,
  EXPR_LT,
  EXPR_GT,
  EXPR_INT_LITERAL,
  EXPR_FLOAT_LITERAL,
  EXPR_CHAR_LITERAL,
  EXPR_STR_LITERAL,
  EXPR_VAR,
  EXPR_ASSIGN,
  EXPR_CALL,
  EXPR_ARG
} expr_t;

struct expr {
  expr_t kind;
  struct expr *left;
  struct expr *right;
  const char *var_name; // For variables & functions
  int int_value;        // Used for storing both int and char
  float float_value;
  const char *str_literal;
};

/* Factory for binary operator */
struct expr *expr_create(expr_t kind, struct expr *left, struct expr *right);

/* Factories for leaf types*/
struct expr *expr_create_int_literal(int value);
struct expr *expr_create_float_literal(float value);
struct expr *expr_create_char_literal(char ch);
struct expr *expr_create_string_literal(const char *str);
struct expr *expr_create_var(const char *name);

#endif