#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "symbol.h"

struct symbol *symbol_table;

void insert_symbol(char *name, Type type, void *value) {
	
	struct symbol *new_symbol = (struct symbol *)malloc(sizeof(struct symbol));
	new_symbol->name = strdup(name);
	new_symbol->type = type;
	new_symbol->value = value;
	new_symbol->next = symbol_table;
	symbol_table = new_symbol;
}

struct symbol *lookup_symbol(char *name) {
	
	struct symbol *curr = symbol_table;
	
	while (curr != NULL) {
		
		if (strcmp(curr->name, name) == 0) {
			return curr;
		}
		
		curr = curr->next;
	}
}

void *get_symbol_value(char* name, Type expected_type) {

	struct symbol *sym = lookup_symbol(name);
	if (sym == NULL)
		fprintf(stderr, "Error: Undefined variable %s\n", name);
	
	// Check if the expected type matches the symbol's type
    // if (sym->type != expected_type) {
        // fprintf(stderr, "Error: Type mismatch for variable %s (expected %s, found %s)\n",
                // name, type_to_string(expected_type), type_to_string(symbol->type));
        // exit(1);
    // }
	
	return sym->value;
}