C := /usr/bin/cc
CFLAGS := -Wall -Wextra -g -O2 -march=native

F := /usr/bin/flex
B := /usr/bin/bison
BFLAGS := -d

# source files
# PAR := ./src/parser.c
# LEX := ./src/lexer.c
INT := ./src/interpreter.c
INT_OUT := ./mather

all: $(INT)
	$(CC) $(CFLAGS) -o $(INT_OUT) $(INT)

clean:
	rm -rf *.o $(INT_OUT)

.PHONY: all clean
