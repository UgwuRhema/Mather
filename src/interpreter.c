#include <stdio.h>
#include "parser.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

extern FILE *yyin;

bool is_valid_mather_file(char *);

int
main(int argc, char *argv[])
{
	/* interpreter */
	if (argc < 2)
	{
		fprintf(stderr, "Mather: Error, no input files found\n");
		return 1;
	}
	char *filename = argv[1];
	FILE *fd = fopen(filename, "r");	
	if (!fd)
	{
		fprintf(stderr, "Mather: Error, failed to open %s\n", filename);
		return 1;
	}
	if (!is_valid_mather_file(filename))
	{
		fprintf(stderr, "Mather: Error: failed to load %s, it is not a Mather file'.math'\n"
				, filename);
		exit(1);
	}
	yyin = fd;
	return yyparse();
}

bool
is_valid_mather_file(char *filename)
{
	if (strlen(filename) < 5) return false;
	return strcmp(filename + strlen(filename) - 5, ".math") == 0;
}
