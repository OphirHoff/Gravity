#ifndef EXPR_H
#define EXPR_H

typedef enum {
	EXPR_ADD,
	EXPR_SUBTRACT,
	EXPR_DIVIDE,
	EXPR_MULTIPLY,
	EXPR_VALUE,
	EXPR_VAR,
	EXPR_FUNCTION,
	EXPR_ASSIGN,
	EXPR_LIST
} expr_t;

struct expr {
	expr_t kind;
	struct expr *left;
	struct expr *right;
	float value;
	
	// For variables & functions
	char *var_name;
	
	// For functions
	void *arg;
	
	// For Expression lists
	struct expr *list;
};



// Function Declarations
struct expr *expr_create(expr_t kind, struct expr *left, struct expr *right);
struct expr *expr_create_dval(float value);
struct expr *expr_create_ival(int value);
struct expr *expr_create_var(char *name);
struct expr *expr_create_func(char *name, struct expr *exp);
struct expr * expr_create_list( struct expr * left, struct expr * right );

#endif