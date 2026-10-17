%{
#include <stdio.h>
/* declarations */
int yylex(void);
void yyerror(const char *s);
extern char *yytext;
extern int yylineno;
%}

%define parse.error verbose

%token NUM_TOK "'Number'"
