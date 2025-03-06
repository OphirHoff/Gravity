#ifndef SYMBOL_H
#define SYMBOL_H

typedef enum {
	TYPE_FLOAT
} Type;

struct symbol {
	char *name;
	Type type;
	void *value;
	struct symbol *next;
};

void print_sym_tbl(struct symbol *table);
void insert_symbol(char *name, Type type, void *value);
struct symbol *lookup_symbol(char *name);
void *get_symbol_value(char* name, Type expected_type);

#endif