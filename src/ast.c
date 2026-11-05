#include "ast.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct arglist *
arglist_create(void)
{
	struct arglist *narg = (struct arglist *)malloc(sizeof(struct arglist));
	if (!narg)
		return NULL;
	narg->items = NULL;
	narg->count = 0;
	return narg;
}

void
arglist_push(struct arglist *list, struct expr *expr)
{
	if (!list || !expr)
		return;
	if (!list->items) {
		list->items = (struct expr **)malloc(sizeof(struct expr *));
		if (!list->items)
			return;
		list->items[list->count++] = expr;
		return;
	}
	list->items = (struct expr **)realloc(list->items, (list->count + 1) * sizeof(struct expr *));
	if (!list->items)
	{
		fprintf(stderr, "Reallocation error!\n");
		return;
	}
	list->items[list->count++] = expr;
}

struct expr *
expr_num(double value)
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

struct expr *
expr_call(char *name, struct arglist *args, size_t argc)
{
	if (!name || !args)
		return NULL;
	struct expr *ne = (struct expr *)malloc(sizeof(struct expr));
	if (!ne) return NULL;
	ne->type = EXPR_CALL;
	ne->as.call.name = strdup(name);
	ne->as.call.args = args;
	ne->as.call.argc = argc;
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

/*it is not like a print statement at all, and in Mather*/
/*strings cannot be assigned to variables, only printed*/
struct stmt *
stmt_print_string(char *str)
{
	if (!str)
		return NULL;
	struct stmt *ns = (struct stmt *)malloc(sizeof(struct stmt));
	if (!ns) return NULL;
	ns->type = PRINT_STRING_STMT;
	size_t len = strlen(str);
	ns->as.print_str = (char *)malloc(len + 1);
	if (!ns->as.print_str)
	{
		free((void *)ns);
		return NULL;
	}
	strcpy(ns->as.print_str, str);
	ns->as.print_str[len] = '\0';/*i think strcpy null terminates but just to be safe*/
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
	if (!e) return NULL;
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

void
stmt_free(struct stmt *stat)
{
	if (!stat) return;
	switch(stat->type)
	{
		case PRINT_STMT:
			expr_free(stat->as.print);
			free((void *)stat);
			break;
		case PRINT_STRING_STMT:
			free((void *)stat->as.print_str);
			free((void *)stat);
			break;
		case ASSIGN_STMT:
			free((void *)stat->as.assign.name);
			expr_free(stat->as.assign.value);
			free((void *)stat);
			break;
		case EXPR_STMT:
			expr_free(stat->as.expr);
			free((void *)stat);
			break;
		default:
			fprintf(stderr, "Abort due unknown Statement node type\n");
			abort();
			break;
	}
	return;
}

struct tree *
tree_new(void)
{
	struct tree *nt = (struct tree *)malloc(sizeof(struct tree));
	if (!nt) return NULL;
	nt->statements = NULL;
	nt->count = 0;
	return nt;
}

void
tree_add_stmt(struct tree *tree, struct stmt *stat)
{
	if (!tree || !stat)
		return;
	if (!tree->statements)
	{
		tree->statements = stat;
	} else {
		stat->next = tree->statements;
		tree->statements = stat;/*insert at head*/
	}
	tree->count++;
}

struct stmt * 
reverse_stmt_list(struct tree *tree)
{
	if (!tree) return NULL;
	struct stmt *prev = NULL;
	struct stmt *curr = tree->statements;
	while (curr)
	{
		struct stmt *next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	return prev;
}

void
tree_free(struct tree *tree)
{
	if (!tree) return;
	struct stmt *s = tree->statements;
	while (s)
	{
		struct stmt *n = s->next;
		stmt_free(s);
		s = n;
	}
	free((void *)tree);
}
