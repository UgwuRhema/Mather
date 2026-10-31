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
	if (!ne->as.ident)
	{
		free(ne);
		return NULL;
	}
	return ne;
}

struct expr *
expr_binary(enum OP_TYPE t, struct expr *left, struct expr *right)
{
	/*if null why bother free them?*/
	if (left == NULL || right == NULL)
	{
		expr_free(left);
		expr_free(right);
		return NULL;
	}
	struct expr *ne = (struct expr *)malloc(sizeof(struct expr));
	if (!ne)
	{
		expr_free(left);
		expr_free(right);
		return NULL;
	}
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
			abort();
			break;
	}
	return;
}

struct stmt *
stmt_print(struct expr *print)
{
	if (!print) return NULL;
	struct stmt *ns = (struct stmt *)malloc(sizeof(struct stmt));
	if (!ns)
	{
		expr_free(print);
		return NULL;
	}
	ns->type = PRINT_STMT;
	ns->as.print = print;
	ns->next = NULL;
	return ns;
}

struct stmt *
stmt_assign(char *id, struct expr *exp)
{
	if (!exp || !id)
	{
		expr_free(exp);
		return NULL;
	}
	struct stmt *ns = (struct stmt *)malloc(sizeof(struct stmt));
	if (!ns)
	{
		expr_free(exp);
		return NULL;
	}
	ns->type = ASSIGN_STMT;
	ns->as.assign.name = strdup(id);
	if (!ns->as.assign.name)
	{
		free((void *)ns);
		expr_free(exp);
		return NULL;
	}
	ns->as.assign.value = exp;
	ns->next = NULL;
	return ns;
}

struct stmt *
stmt_expr(struct expr *e)
{
	if (e) return NULL;
	struct stmt *ns = (struct stmt *)malloc(sizeof(struct stmt));
	if (!ns)
	{
		expr_free(e);
		return NULL;
	}
	ns->type = EXPR_STMT;
	ns->as.expr= e;
	ns->next = NULL;
	return ns;
}
