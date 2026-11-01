#include "exe.h"
#include <stdio.h>

bool
eval_expr(struct expr *expr, struct symbol_table *symbols, int *out)
{
	if (!expr || !symbols || !out) return false;
	switch (expr->type)
	{
		case EXPR_NUM:
			*out = expr->as.num;
			return true;
		case EXPR_IDENT:
			if (!symbol_get(symbols, expr->as.ident, out))
			{
				fprintf(stderr, "Mather: Error: Undeffined variable \"%s\"\n", expr->as.ident);
				return false;
			}
			return true;
		case EXPR_BINARY:
			int left, right;
			if (!eval_expr(expr->as.binary.left, symbols, &left)) return false;
			if (!eval_expr(expr->as.binary.right, symbols, &right)) return false;
			switch(expr->as.binary.op)
			{
				case OP_ADD:
					*out = left + right;
					break;
				case OP_SUB:
					*out = left - right;
					break;
				case OP_MUL:
					*out = left * right;
					break;
				case OP_DIV:
					if (right == 0)
					{
						fprintf(stderr, "Mather: Error: Division by zero\n");
						return false;
					}
					*out = left / right;
					break;
				default:
					return false;
			}
			return true;
		default:
			return false;
	}
	return false;
}

bool
execute_stmt(struct stmt *stmt, struct symbol_table *symbols)
{
	if (!stmt || !symbols) return false;
	switch (stmt->type)
	{
		case PRINT_STMT:
			int out;
			if (!eval_expr(stmt->as.print, symbols, &out))
			{
				fprintf(stderr, "Mather: Error: Failed to evaluate the expression\n");
				return false;
			}
			printf("%s", stmt->as.print->as.ident);
			return true;
		case ASSIGN_STMT:
			int out2;
			if (!eval_expr(stmt->as.assign.value, symbols, &out2))
			{
				fprintf(stderr, "Mather: Error: Failed to evaluate the expression\n");
				return false;
			}
			/*add to symbol table so we can keep track of variables*/
			if (!symbol_set(symbols, stmt->as.assign.name, out))
			{
				fprintf(stderr, "Mather: Error: Unable to assign value to variable\n");
				return false;
			}
			return true;
		case EXPR_STMT:
			int out3;
			if (!eval_expr(stmt->as.expr, symbols, &out3))
			{
				fprintf(stderr, "Mather: Error: Failed to evaluate the expression\n");
				return false;
			}
			/*we don't use value*/
			return true;
		default:
			return false;
	}
	return false;
}

bool
execute_tree(struct tree *tree)
{
	/* TODO: create a symbol table, reverse the list exactly once with
	 * tree->statements = reverse_stmt_list(tree);
	 * execute each statement, then free the symbol table.
	 */
	(void)tree;
	return false;
}
