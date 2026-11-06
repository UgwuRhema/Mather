%{
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
/* declarations */
int yylex(void);
void yyerror(const char *s);
extern char *yytext;
extern int yylineno;
struct tree *root = NULL;
%}

%define parse.error verbose

%union {
	char *str;
	double num;
	struct expr *expr;
	struct stmt *stat;
	struct tree *tree;
	struct arglist *arglist;
}

%token START_TOK "'Start label'"
%token PRINT_TOK "'Print'"
%token INPUT_TOK "'Collect'"
%token <num> NUM_TOK "'Number'"
%token <str> IDENT_TOK "'Identifier'"
%token ASSIGN_TOK "'='"
%token ADD_TOK "'+'"
%token MINUS_TOK "'-'"
%token DIV_TOK "'/'"
%token MUL_TOK "'*'"
%token SEMICOLON_TOK "';'"
%token COLON_TOK "':'"
%token LEFTPAREN_TOK "'('"
%token RIGHTPAREN_TOK "')'"
%token GTHAN_TOK "'>'"
%token LTHAN_TOK "'<'"
%token <str>STRING_TOK "'String'"
%token COMMA_TOK "','"

%type <expr> expr term factor
%type <arglist> call_args
%type <stat> statement print_stmt assign_stmt
%type <tree> program statements

%%

program: START_TOK COLON_TOK statements {
			$$ = $3;
			root = $3;
		}
	   ;

statements: %empty  {
				$$ = tree_new();
			}
		  | statements statement {
				tree_add_stmt($1, $2);
				$$ = $1;
			}
		  ;

statement: print_stmt { $$ = $1; }
		 | assign_stmt { $$ = $1; }
		 | expr SEMICOLON_TOK { $$ = stmt_expr($1); }
		 ;

/* YES! this is an  interpreter BUT i will never exempt the semi-colon */
print_stmt: PRINT_TOK expr SEMICOLON_TOK {
				$$ = stmt_print($2);	
			}
			| PRINT_TOK STRING_TOK SEMICOLON_TOK {
				$$ = stmt_print_string($2);
			}
			;

/* NEVER exempt SemiColon */
assign_stmt: IDENT_TOK ASSIGN_TOK expr SEMICOLON_TOK {
				$$ = stmt_assign($1, $3);
			}
			;

expr: term { $$ = $1; }
	| expr ADD_TOK term { $$ = expr_binary(OP_ADD, $1, $3); }
	| expr MINUS_TOK term { $$ = expr_binary(OP_SUB, $1, $3);}
;

term: factor { $$ = $1; }
	| term MUL_TOK factor { $$ = expr_binary(OP_MUL, $1, $3); }
	| term DIV_TOK factor { $$ = expr_binary(OP_DIV, $1, $3); }
	;

factor: NUM_TOK { $$ = expr_num($1); }
	  | IDENT_TOK { $$ = expr_ident($1); }
	  | LEFTPAREN_TOK expr RIGHTPAREN_TOK { $$ = $2; }
	  | input_expr { $$ = expr_input(); }
	  | IDENT_TOK LEFTPAREN_TOK call_args RIGHTPAREN_TOK { $$ = expr_call($1, $3); }
	  ;

/*fake function call*/
input_expr: INPUT_TOK SEMICOLON_TOK {
			}
			;

call_args: expr {
			$$ = arglist_create();
			if(!arglist_push($$, $1)) /*push the new expression onto the argument list*/
			{
				fprintf(stderr, "Mather: Parser Error: Failed to push expr unto arglist\n");
			}
		 }
		 | call_args COMMA_TOK expr { 
			if (!arglist_push($1, $3))
			{
				fprintf(stderr, "Mather: Parser Error: Failed to push new expr onto arglist\n");
			}
			$$ = $1;
		 }
		 ;

%%

void 
yyerror(const char *s)
{
	fprintf(stderr, "Mather: line %d: %s near '%s'\n", yylineno, s, yytext);
}
