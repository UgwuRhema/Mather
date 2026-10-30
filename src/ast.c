#include "ast.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct expr *
expr_num(int value)
{
	struct expr *ne = (struct expr *)malloc(sizeof(struct expr));	
	if (!ne) return NULL;
	ne->type = EXPR_NUM;
	ne->as.num = value;
	return ne;
}

struct expr *
expr_ident(char *id)
{
	struct expr *ne = (struct expr *)malloc(sizeof(struct expr));
	if (!ne) return NULL;
	ne->type = EXPR_IDENT;
	ne->as.ident = strdup(id);
	return ne;
}

struct expr *
expr_binary(enum OP_TYPE t, struct expr *left, struct expr *right)
{
	if (left == NULL || right == NULL) return NULL;
	struct expr *ne = (struct expr *)malloc(sizeof(struct expr));
	if (!ne) return NULL;
	ne->type = EXPR_BINARY;
	ne->as.binary.op = t;
	ne->as.binary.left = left;
	ne->as.binary.right = right;
	return ne;
}

void
expr_free(struct expr *e)
{
	if (!e) return;
	switch(e->type)
	{
		case EXPR_NUM:
			/*just free the main expr node*/
			free((void *)e);
			break;
		case EXPR_IDENT:
			free((void *)e->as.ident);
			free((void *)e);
			break;
		case EXPR_BINARY:
			expr_free(e->as.binary.left);
			expr_free(e->as.binary.right);
			free((void *)e);
			break;
		default:
			fprintf(stderr, "Invalid option while freeing expression node\n");
			free((void *)e);
			break;
	}
	return;
}
