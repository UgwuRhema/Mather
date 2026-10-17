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

"print->" {
	return PRINT_TOK;
}

[0-9]+ {
	yylval.num = atoi(yytext);
	return NUM_TOK;
}

"\\".* {
	/* skip my comments */
}

[ \t\r\n]+ {
	/* skip whitespace */
}

[a-zA-Z_][a-zA-Z0-9_]* {
	yylval.str = strdup(yytext);
	return IDENT_TOK;
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

. { fprintf(stderr, "Mather: Error, Unknown character '%s'\n", yytext); }

%%
