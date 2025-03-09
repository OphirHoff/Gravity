#include "debug\debug.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Function prototype for the lexer */
extern int yylex();
extern int yyparse();
extern FILE *yyin; // Flex input file stream

extern struct decl *parser_result;

int main(int argc, char *argv[]) {

  if (argc > 1) {
    yyin = fopen(argv[1], "r"); // Open the file if provided
    if (!yyin) {
      perror("Error opening file");
      return EXIT_FAILURE;
    }
  }

  if (argc > 2) {
    if (strcmp(argv[2], "-d") == 0 || strcmp(argv[2], "--debug") == 0) {
      DEBUG = 1;
    }
  }

  printf("Parsing started...\n");

  if (yyparse() == 0) {
    printf("Parsing completed successfully!\n");

    if (DEBUG)
      print_ast(parser_result);

  } else {
    printf("Parsing failed.\n");
  }

  if (yyin) {
    fclose(yyin);
  }

  return EXIT_SUCCESS;
}
