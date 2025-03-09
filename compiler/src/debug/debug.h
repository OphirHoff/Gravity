#ifndef DEBUG_H
#define DEBUG_H

#include "..\AST\decl.h"
#include "..\AST\expr.h"
#include "..\AST\stmt.h"

extern int DEBUG;

void decl_print(struct decl *d, int indent);
void type_print(struct type *t, int indent);
void expr_print(struct expr *e, int indent);
void param_list_print(struct param_list *p, int indent);
void stmt_print(struct stmt *s, int indent);
void print_ast(struct decl *d);

#endif