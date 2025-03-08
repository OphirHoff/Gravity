#ifndef DECL_H
#define DECL_H

typedef enum {
  // TYPE_VOID,
  TYPE_INTEGER,
  TYPE_DECIMAL,
  TYPE_CHARACTER,
  TYPE_STRING,
  TYPE_FUNCTION
  // TYPE_ARRAY
} type_t;

struct type {
  type_t kind;
  struct type *subtype;      // Compound types (e.g. array, function)
  struct param_list *params; // Function parameters
};

/* Function parameters are expressed as a linked list */
struct param_list {
  char *name;
  struct type *type;
  struct param_list *next;
};

struct decl {
  char *name;
  struct type *type;
  struct expr *value;
  struct stmt *code;
  struct decl *next;
};

struct type *type_create(type_t kind, struct type *subtype,
                         struct param_list *params);

struct decl *decl_create(char *name, struct type *type, struct expr *value,
                         struct stmt *code, struct decl *next);

struct param_list *param_create(char *name, struct type *type,
                                struct param_list *next);

#endif