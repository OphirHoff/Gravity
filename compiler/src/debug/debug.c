#include "debug.h"
#include "..\AST\decl.h"
#include "..\AST\expr.h"
#include "..\AST\stmt.h"
#include <stdio.h>

int DEBUG = 0; // Default: debugging is off

void decl_print(struct decl *d, int indent) {
  if (!d)
    return;

  for (int i = 0; i < indent; i++) {
    printf("  ");
  }
  printf("Declaration: %s\n", d->name);

  for (int i = 0; i < indent; i++) {
    printf("  ");
  }
  printf("  Type: ");
  type_print(d->type, indent + 1);

  if (d->value) {
    for (int i = 0; i < indent; i++) {
      printf("  ");
    }
    printf("  Value: ");
    expr_print(d->value, indent + 1);
  }

  if (d->code) {
    for (int i = 0; i < indent; i++) {
      printf("  ");
    }
    printf("  Code:\n");
    stmt_print(d->code, indent + 1);
  }

  if (d->next) {
    decl_print(d->next, indent);
  }
}

void type_print(struct type *t, int indent) {
  if (!t)
    return;

  for (int i = 0; i < indent; i++) {
    printf("  ");
  }

  switch (t->kind) {
  case TYPE_INTEGER:
    printf("integer\n");
    break;
  case TYPE_DECIMAL:
    printf("decimal\n");
    break;
  case TYPE_CHARACTER:
    printf("character\n");
    break;
  case TYPE_STRING:
    printf("string\n");
    break;
  case TYPE_FUNCTION:
    printf("function\n");
    if (t->params) {
      for (int i = 0; i < indent; i++) {
        printf("  ");
      }
      printf("  Parameters:\n");
      param_list_print(t->params, indent + 1);
    }
    break;
  // Add other cases for array, etc. as needed
  default:
    printf("unknown\n");
    break;
  }

  if (t->subtype) {
    for (int i = 0; i < indent; i++) {
      printf("  ");
    }
    printf("  Subtype: ");
    type_print(t->subtype, indent + 1);
  }
}

void expr_print(struct expr *e, int indent) {
  if (!e)
    return;

  for (int i = 0; i < indent; i++) {
    printf("  ");
  }

  switch (e->kind) {
  case EXPR_ADD:
    printf("+\n");
    expr_print(e->left, indent + 1);
    expr_print(e->right, indent + 1);
    break;
  case EXPR_SUB:
    printf("-\n");
    expr_print(e->left, indent + 1);
    expr_print(e->right, indent + 1);
    break;
  case EXPR_MUL:
    printf("*\n");
    expr_print(e->left, indent + 1);
    expr_print(e->right, indent + 1);
    break;
  case EXPR_DIV:
    printf("/\n");
    expr_print(e->left, indent + 1);
    expr_print(e->right, indent + 1);
    break;
  case EXPR_INC:
    printf("++\n");
    expr_print(e->left, indent + 1);
    break;
  case EXPR_DEC:
    printf("--\n");
    expr_print(e->left, indent + 1);
    break;
  case EXPR_LT:
    printf("<\n");
    expr_print(e->left, indent + 1);
    expr_print(e->right, indent + 1);
    break;
  case EXPR_GT:
    printf(">\n");
    expr_print(e->left, indent + 1);
    expr_print(e->right, indent + 1);
    break;
  case EXPR_INT_LITERAL:
    printf("INT: %d\n", e->int_value);
    break;
  case EXPR_FLOAT_LITERAL:
    printf("FLOAT: %f\n", e->float_value);
    break;
  case EXPR_CHAR_LITERAL:
    printf("CHAR: %c\n", (char)e->int_value);
    break;
  case EXPR_STR_LITERAL:
    printf("STRING: %s\n", e->str_literal);
    break;
  case EXPR_VAR:
    printf("VAR: %s\n", e->var_name);
    break;
  case EXPR_ASSIGN:
    printf("=\n");
    expr_print(e->left, indent + 1);
    expr_print(e->right, indent + 1);
    break;
  case EXPR_CALL:
    printf("CALL\n");
    expr_print(e->left, indent + 1);
    expr_print(e->right, indent + 1);
    break;
  case EXPR_ARG:
    printf("ARG\n");
    expr_print(e->left, indent + 1);
    expr_print(e->right, indent + 1);
    break;
  default:
    printf("unknown\n");
    break;
  }
}

void param_list_print(struct param_list *p, int indent) {
  if (!p)
    return;

  for (int i = 0; i < indent; i++) {
    printf("  ");
  }
  printf("Parameter: %s\n", p->name);

  for (int i = 0; i < indent; i++) {
    printf("  ");
  }
  printf("  Type: ");
  type_print(p->type, indent + 1);

  if (p->next) {
    param_list_print(p->next, indent);
  }
}

void stmt_print(struct stmt *s, int indent) {
  if (!s)
    return;

  for (int i = 0; i < indent; i++) {
    printf("  ");
  }

  switch (s->kind) {
  case STMT_DECL:
    printf("Declaration:\n");
    decl_print(s->decl, indent + 1);
    break;
  case STMT_EXPR:
    printf("Expression:\n");
    expr_print(s->expr, indent + 1);
    break;
  case STMT_IF_ELSE:
    printf("If-Else:\n");
    for (int i = 0; i < indent; i++) {
      printf("  ");
    }
    printf("  Condition:\n");
    expr_print(s->expr, indent + 2);
    for (int i = 0; i < indent; i++) {
      printf("  ");
    }
    printf("  Body:\n");
    stmt_print(s->body, indent + 2);
    if (s->else_body) {
      for (int i = 0; i < indent; i++) {
        printf("  ");
      }
      printf("  Else:\n");
      stmt_print(s->else_body, indent + 2);
    }
    break;
  case STMT_FOR:
    printf("For:\n");

    for (int i = 0; i < indent + 1; i++) {
      printf("  ");
    }
    printf("  Init:\n");
    expr_print(s->init_expr, indent + 2); // Print the initializer expression

    for (int i = 0; i < indent + 1; i++) {
      printf("  ");
    }
    printf("  Condition:\n");
    expr_print(s->expr, indent + 2); // Print the condition expression

    for (int i = 0; i < indent + 1; i++) {
      printf("  ");
    }
    printf("  Increment:\n");
    expr_print(s->next_expr, indent + 2); // Print the increment expression

    for (int i = 0; i < indent + 1; i++) {
      printf("  ");
    }
    printf("  Body:\n");
    stmt_print(s->body, indent + 2); // Print the loop body
    break;
  case STMT_PRINT:
    printf("Print:\n");
    expr_print(s->expr, indent + 1);
    break;
  case STMT_RETURN:
    printf("Return:\n");
    expr_print(s->expr, indent + 1);
    break;
  case STMT_BLOCK:
    printf("Block:\n");
    stmt_print(s->body, indent + 1);
    break;
  default:
    printf("unknown\n");
    break;
  }

  if (s->next) {
    stmt_print(s->next, indent);
  }
}

void print_ast(struct decl *d) {
  printf("Abstract Syntax Tree:\n");
  decl_print(d, 0);
}