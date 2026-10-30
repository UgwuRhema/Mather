#ifndef MATHER_AST_H
#define MATHER_AST_H

enum EXPR_TYPE
{
	EXPR_NUM,
	EXPR_IDENT,
	EXPR_BINARY,
};

enum STMT_TYPE
{
	PRINT_STMT,
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
		int num;
		char *ident;
		struct
		{
			enum OP_TYPE op;
			struct expr *left;
			struct expr *right;
		} binary;
	} as;
};

struct stmt
{
	enum STMT_TYPE type;
	union
	{
		struct expr *print;
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
};

struct expr *expr_num(int value);
struct expr *expr_ident(char *name);
struct expr *expr_binary(enum OP_TYPE op, struct expr *left, struct expr *right);

struct stmt *stmt_print(struct expr *value);
struct stmt *stmt_assign(char *name, struct expr *value);
struct stmt *stmt_expr(struct expr *value);

struct tree *tree_new(void);
void tree_add_stmt(struct tree *tree, struct stmt *stmt);

void expr_free(struct expr *expr);
void stmt_free(struct stmt *stmt);
void tree_free(struct tree *tree);

#endif
