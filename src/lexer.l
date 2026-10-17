%{
#include <stdio.h>
%}

%option yylineno
%option noyywrap

%%

[0-9]+ {
	printf("Number\n");
}

"\\".* {
	/* skip my comments */
}

[a-zA-Z_][a-zA-Z0-9_]* {
	printf("Identifier\n");
}

. {
	fprintf(stderr, "Unknow character '%s'\n", yytext);
}

%%

int main(int argc, char *argv[])
{
	yylex();
	return 0;
}
