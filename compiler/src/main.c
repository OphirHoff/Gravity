#include <stdio.h>
#include <stdlib.h>

/* Function prototype for the lexer */
extern int yylex();
extern int yyparse();
extern FILE *yyin; // Flex input file stream

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
  } else {
    printf("Parsing failed.\n");
  }

  if (yyin) {
    fclose(yyin);
  }

  return EXIT_SUCCESS;
}
