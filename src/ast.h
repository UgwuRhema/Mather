#ifndef MATHER_AST_H
#define MATHER_AST_H

#include <stddef.h>
#include <stdbool.h>

enum EXPR_TYPE
{
	EXPR_NUM,
	EXPR_IDENT,
	EXPR_BINARY,
	EXPR_INPUT,
	EXPR_CALL,
};

enum STMT_TYPE
{
	PRINT_STMT,
	PRINT_STRING_STMT,
	ASSIGN_STMT,
	EXPR_STMT,
};

enum OP_TYPE
{
	OP_ADD,
	OP_SUB,
	OP_MUL,
	OP_DIV,
};

struct expr
{
	enum EXPR_TYPE type;
	union
	{
		double num;
		char *ident;
		struct
		{
			enum OP_TYPE op;
			struct expr *left;
			struct expr *right;
		} binary;
		struct 
		{
			char *name;
			struct arglist *args;
			size_t argc;
		} call;
	} as;
};

struct arglist
{
	struct expr **items;
	size_t count;
};

struct stmt
{
	enum STMT_TYPE type;
	union
	{
		struct expr *print;
		char *print_str;
		struct
		{
			char *name;
			struct expr *value;
		} assign;
		struct expr *expr;
	} as;
	struct stmt *next;
};

struct tree
{
	struct stmt *statements;
	size_t count;
};

struct arglist *arglist_create(void);//
bool arglist_push(struct arglist *, struct expr *);//

struct expr *expr_num(double);//
struct expr *expr_ident(char *);//
struct expr *expr_binary(enum OP_TYPE, struct expr *, struct expr *);//
struct expr *expr_input(void);
struct expr *expr_call(char *, struct arglist *);

struct stmt *stmt_print(struct expr *);//
struct stmt *stmt_print_string(char *, int);
struct stmt *stmt_assign(char *, struct expr *);//
struct stmt *stmt_expr(struct expr *);//

struct tree *tree_new(void);//
void tree_add_stmt(struct tree *, struct stmt *);//
struct stmt *reverse_stmt_list(struct tree *);

void expr_free(struct expr *);//
void stmt_free(struct stmt *);//
void tree_free(struct tree *);
#endif
