#include <stdio.h>
#include "parser.h"

extern FILE *yyin;

int
main(int argc, char *argv[])
{
	/* interpreter */
	if (argc < 2)
	{
		fprintf(stderr, "Mather: Error, no input files found\n");
		return 1;
	}

	FILE *fd = fopen(argv[1], "r");	
	yyin = fd;

	return yyparse();
}
