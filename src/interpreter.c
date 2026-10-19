#include <stdio.h>
#include "parser.h"
#include <string.h>
#include <stdlib.h>

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

	const char *filename = strdup(argv[1]);
	FILE *fd = fopen(filename, "r");	
	if (!fd)
	{
		fprintf(stderr, "Mather: Error, failed to open %s\n", filename);
		return 1;
	}
	yyin = fd;

	return yyparse();
}
