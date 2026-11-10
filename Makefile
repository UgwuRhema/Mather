C := /usr/bin/cc
CFLAGS := -Wall -Wextra -g -O2 -march=native

F := /usr/bin/flex
B := /usr/bin/bison
BFLAGS := -d

# source files
PAR := ./src/parser.y
PAR_OUT := ./src/parser.c
LEX := ./src/lexer.l
LEX_OUT := ./src/lexer.c
AST :=./src/ast.c
SYM := ./src/symbol.c
INT := ./src/interpreter.c
INT_OUT := ./mather
EXE := ./src/exe.c

all: $(INT)
	$(MAKE) -C . lex
	$(MAKE) -C . parse
	$(CC) $(CFLAGS) -o $(INT_OUT) $(INT) $(PAR_OUT) $(LEX_OUT) $(AST) $(SYM) $(EXE) -lfl -lm

lex:
	$(F) -o $(LEX_OUT) $(LEX)

parse:
	$(B) $(BFLAGS) -o $(PAR_OUT) $(PAR)

lp:
	$(CC) $(CFLAGS) -o $(INT_OUT) $(LEX_OUT) $(PAR_OUT) -lfl 

clean:
	rm -rf *.o $(INT_OUT)

.PHONY: all clean
