C := /usr/bin/cc
CFLAGS := -Wall -Wextra -g -O2 -march=native

F := /usr/bin/flex
B := /usr/bin/bison
BFLAGS := -d

# source files
# PAR := ./src/parser.y
LEX := ./src/lexer.l
LEX_OUT := ./src/lexer.c
INT := ./src/interpreter.c
INT_OUT := ./mather

all: $(INT)
	$(CC) $(CFLAGS) -o $(INT_OUT) $(INT)

lex:
	$(F) -o $(LEX_OUT) $(LEX)
	#the line below is temporary!
	$(CC) $(CFLAGS) -o $(INT_OUT) $(LEX_OUT) -lfl

clean:
	rm -rf *.o $(INT_OUT)

.PHONY: all clean
