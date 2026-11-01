#include <stdio.h>
#include "parser.h"
#include "ast.h"
#include "exe.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

extern FILE *yyin;
extern struct tree *root;

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
		fclose(fd);
		exit(1);
	}
	yyin = fd;
	/*we parse and get the return value, which is just zero*/
	int result = yyparse();
	/*we execute here*/
	execute_tree(root);
	/*let's clean here*/
	if (root)
	{
		tree_free(root);
		root = NULL;
	}
	fclose(fd);
	return result;
}

bool
is_valid_mather_file(char *filename)
{
	if (strlen(filename) < 5) return false;
	return strcmp(filename + strlen(filename) - 5, ".math") == 0;
}
