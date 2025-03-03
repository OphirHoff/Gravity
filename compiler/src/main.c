#include <stdio.h>
#include <stdlib.h>

/* Bison-generated header file */
#include "..\build\token.h"
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
        printf("Leaf(Value: %d)\n", node->value);
    }

    /* Recursively print children */
    if (node->left) {
        print_ast(node->left, depth + 1);
    }
    if (node->right) {
        print_ast(node->right, depth + 1);
    }
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
    } else {
        printf("Parsing failed.\n");
    }

    if (yyin) {
        fclose(yyin);
    }

    return EXIT_SUCCESS;
}
