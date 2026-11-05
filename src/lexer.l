%{
#include <stdio.h>
#include "parser.h"
%}

%option yylineno
%option noyywrap

%%

"start" {
	return START_TOK;
}

"print" {
	return PRINT_TOK;
}

"funct" {
	return FUNC_TOK;
}

"-"?[0-9]+(\.[0-9]+)? {
	yylval.num = atof(yytext);
	return NUM_TOK;
}

"\\".* {
	/* skip my comments */
}

[ \t\r\n]+ {
	/* skip whitespace */
	/* it definitely does! */
}

[a-zA-Z_][a-zA-Z0-9_]* {
	yylval.str = strdup(yytext);
	return IDENT_TOK;
}

\"([^\"\\]|\\.)*\" {
	yylval.str = strdup(yytext + 1);
	yylval.str[strlen(yylval.str) - 1] = '\0';
	return STRING_TOK;
}

"=" { return ASSIGN_TOK; }
"+" { return ADD_TOK; }
"-" { return MINUS_TOK; }
"/" { return DIV_TOK; }
"*" { return MUL_TOK; }
";" { return SEMICOLON_TOK; }
":" { return COLON_TOK; }
"(" { return LEFTPAREN_TOK; }
")" { return RIGHTPAREN_TOK; }
">"  { return GTHAN_TOK; }
"<"  { return LTHAN_TOK; }

. { fprintf(stderr, "Mather: Error, Unknown character '%s'\n", yytext); }

%%
