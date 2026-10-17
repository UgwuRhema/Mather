%{
#include <stdio.h>
/* declarations */
int yylex(void);
void yyerror(const char *s);
extern char *yytext;
extern int yylineno;
%}

%define parse.error verbose

%token START_TOK "'Start label'"
%token PRINT_TOK "'Print'"
%token NUM_TOK "'Number'"
%token IDENT_TOK "'Identifier'"
%token ASSIGN_TOK "'Equals operator'"
%token ADD_TOK "'Addition operator'"
%token MINUS_TOK "'Minus operator'"
%token DIV_TOK "'Division operator'"
%token MUL_TOK "'Multiplication operator'"
%token SEMICOLON_TOK "';'"
%token LEFTPAREN_TOK "'('"
%token RIGHTPAREN_TOK "')'"
