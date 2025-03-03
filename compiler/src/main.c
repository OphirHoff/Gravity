#include <stdio.h>
#include <stdlib.h>

/* Bison-generated header file */
// #include "..\build\token.h"
#include "AST\expr.h"

extern struct expr *parser_result;

/* Function prototype for the lexer */
extern int yylex();
extern int yyparse();
extern FILE *yyin; // Flex input file stream

/* Function to print the AST in a readable format */
void print_ast(struct expr *node, int depth) {
    if (!node) return;

    /* Indent according to tree depth */
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }

    /* Print node information */
    if (node->left || node->right) {
        printf("Node(kind: %d)\n", node->kind);
    } else {
        printf("Leaf(Value: %g)\n", node->value);
    }

    /* Recursively print children */
    if (node->left) {
        print_ast(node->left, depth + 1);
    }
    if (node->right) {
        print_ast(node->right, depth + 1);
    }
}

float expr_evaluate(struct expr *node) {

	if (!node) return 0;
	
	float l_value = expr_evaluate(node->left);
	float r_value = expr_evaluate(node->right);
	
	printf("left: %g, right: %g, kind: %d\n", l_value, r_value, node->kind);
	
	switch (node->kind) {
		
		case EXPR_VALUE:
			return node->value;
		case EXPR_ADD:
			return l_value + r_value; break;
		case EXPR_SUBTRACT:
			return l_value - r_value; break;
		case EXPR_MULTIPLY:
			return l_value * r_value; break;
		case EXPR_DIVIDE:
			return l_value / r_value; break;
		default:
			printf("Invalid token type encountered\n");
			return 0;
	}
}

/* Function to determine where parentheses are needed for a in the AST */
int paren_needed(struct expr *node) {
	/*
	output:
	0 -> if no parentheses needed
	1 -> if parentheses needed only on the left side
	2 -> if parentheses needed only on the right side
	3 -> if parentheses needed on both left & right
	*/
	
	if ( node->kind == EXPR_MULTIPLY || node->kind == EXPR_DIVIDE ) {
		
		int left_need = node->left->kind == EXPR_ADD || node->left->kind == EXPR_SUBTRACT;
		int right_need = node->right->kind == EXPR_ADD || node->right->kind == EXPR_SUBTRACT;
		
		if ( left_need & !right_need )
			return 1;
		if ( !left_need & right_need )
			return 2;
		if ( left_need & right_need )
			return 3;		
	}
	
	return 0;
}		

void expr_print(struct expr *node) {
	
	if (!node) return;
	
	int where_paren = paren_needed(node);
	
	if (where_paren == 1 || where_paren == 3)
		printf("(");
	
	expr_print(node->left);
	
	if (paren_needed(node) == 1 || paren_needed(node) == 3)
		printf(")");
	
	switch (node->kind) {
		
		case EXPR_VALUE:
			printf("%g", node->value); break;
		case EXPR_ADD:
			printf("+"); break;
		case EXPR_SUBTRACT:
			printf("-"); break;
		case EXPR_MULTIPLY:
			printf("*"); break;
		case EXPR_DIVIDE:
			printf("/"); break;
		default:
			printf("Invalid token type encountered\n");
	}
	
	if (paren_needed(node) == 2 || paren_needed(node) == 3)
		printf("(");
	
	expr_print(node->right);
	
	if (paren_needed(node) == 2 || paren_needed(node) == 3)
		printf(")");
	
	
}

int main(int argc, char **argv) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r"); // Open the file if provided
        if (!yyin) {
            perror("Error opening file");
            return EXIT_FAILURE;
        }
    }

    printf("Parsing started...\n");
    
   if (yyparse() == 0) {
        printf("Parsing completed successfully!\n");
        printf("\nAbstract Syntax Tree (AST):\n");
        print_ast(parser_result, 0);  // Print AST with indentation
		printf("\nExpression evaluation: %g\n\n", expr_evaluate(parser_result));
		expr_print(parser_result);
    } else {
        printf("Parsing failed.\n");
    }

    if (yyin) {
        fclose(yyin);
    }

    return EXIT_SUCCESS;
}
