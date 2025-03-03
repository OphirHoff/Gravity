SCAN_DIR = src\scanner
PARSE_DIR = src\parser
AST_DIR = src\AST
BUILD_DIR = build

SRCS = main.c scanner.c
OBJS = main.o scanner.o
EXE = scanner.exe

$(BUILD_DIR):
	if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)

# Generated files
SCANNER_C = $(BUILD_DIR)\scanner.c
PARSER_C = $(BUILD_DIR)\parser.c
TOKEN_H = $(BUILD_DIR)\token.h

$(SCANNER_C): $(SCAN_DIR)\scanner.flex | $(BUILD_DIR)
	flex $<
	ren lex.yy.c scanner.c && move scanner.c $(BUILD_DIR)
	
$(PARSER_C) $(TOKEN_H): $(PARSE_DIR)/parser.bison | $(BUILD_DIR)
	bison --defines=$(TOKEN_H) --output=$(PARSER_C) $(PARSE_DIR)\parser.bison
	
parser: $(SCANNER_C) $(PARSER_C) $(TOKEN_H) $(AST_DIR)\expr.c src\main.c | bin
	gcc -o bin\parser.exe src\main.c $(SCANNER_C) $(PARSER_C) $(AST_DIR)\expr.c

bin:
	if not exist bin mkdir bin

clean:
	if exist $(BUILD_DIR) rmdir /s /q $(BUILD_DIR)
	
clear:
	for %%f in (*.o) do if exist "%%f" move /Y "%%f" trash
	for %%f in (*.c) do if /I not "%%f"=="main1.c" if exist "%%f" move /Y "%%f" trash
	for %%f in (*.h) do if exist "%%f" move /Y "%%f" trash