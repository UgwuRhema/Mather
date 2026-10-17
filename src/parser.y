%{
#include <stdio.h>
/* declarations */
int yylex(void);
void yyerror(const char *s);
extern char *yytext;
extern int yylineno;
%}

%define parse.error verbose

%union {
	char *str;
	int num;
}

%token START_TOK "'Start label'"
%token PRINT_TOK "'Print'"
%token <num> NUM_TOK "'Number'"
%token <str> IDENT_TOK "'Identifier'"
%token ASSIGN_TOK "'Equals operator'"
%token ADD_TOK "'Addition operator'"
%token MINUS_TOK "'Minus operator'"
%token DIV_TOK "'Division operator'"
%token MUL_TOK "'Multiplication operator'"
%token SEMICOLON_TOK "';'"
%token COLON_TOK "':'"
%token LEFTPAREN_TOK "'('"
%token RIGHTPAREN_TOK "')'"

%%

program: start
	   ;

start: start_label
	 ;

start_label: START_TOK COLON_TOK {
				printf("A Start label\n");
			}
			;

%%

extern FILE *yyin;

int
main(int argc, char *argv[])
{
	if (ac > 1)
	{
		FILE *file = fopen(argv[1], "r");
		if (!file)
		{
			perror(argv[1]);
			return 1;
		}
		yyin = file;
	}

	return yyparse();
}
