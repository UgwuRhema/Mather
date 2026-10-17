%{
#include <stdio.h>
%}

%option yylineno
%option noyywrap

%%

"start:" {
	return START_TOK;
}

"print->" {
	return PRINT_TOK;
}

[0-9]+ {
	return NUM_TOK;
}

"\\".* {
	/* skip my comments */
}

[ \t\r\n]+ {
	/* skip whitespace */
}

[a-zA-Z_][a-zA-Z0-9_]* {
	return IDENT_TOK;
}

"=" { return ASSIGN_TOK; }
"+" { return ADD_TOK; }
"-" { return MINUS_TOK; }
"/" { return DIV_TOK; }
"*" { return MUL_TOK; }
";" { return SEMICOLON_TOK; }
"(" { return LEFTPAREN_TOK; }
")" { return RIGHTPAREN_TOK; }

%%

int main(int argc, char *argv[])
{
	yylex();
	return 0;
}
