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
	if (strcmp(argv[1], "--help") == 0)
	{
		printf("Mather Interpreter\n\n");
		printf("Usage: mather [options] <mather source file> \n");
		printf("\tOptions:\n\t--help:\tDisplay this information\n");
		printf("To run against a Mather file:\tmather \"file.math\"\n");
		return 0;
	}
	/*get filename for CLA*/
	char *filename = argv[1];
	FILE *fd = fopen(filename, "r");	
	if (!fd)
	{
		fprintf(stderr, "Mather: Error, failed to open %s\n", filename);
		return 1;
	}
	/*match file against extension format*/
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
	if (result != 0)
	{
		fprintf(stderr, "Mather: Error: Parsing failed\n");
		fclose(fd);
		return 1;
	}
	/*we execute here*/
	/*on when the final tree is comstructted, we reverse once and that's all*/
	root->statements = reverse_stmt_list(root);
	struct symbol_table *global_symbol = symbol_table_new();
	if(!execute_tree(root, global_symbol))
	{
		fprintf(stderr, "Mather: Error: Failed to execute statements in tree\n");
		symbol_table_free(global_symbol);
		tree_free(root);
		root = NULL;
		fclose(fd);
		exit(1);
	}
	symbol_table_free(global_symbol);
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
