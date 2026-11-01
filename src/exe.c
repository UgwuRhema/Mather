#include "exe.h"

bool
eval_expr(struct expr *expr, struct symbol_table *symbols, int *out)
{
	if (!expr || !symbols || !out) return false;
	switch (expr->type)
	{
		case EXPR_NUM:
			*out = expr->as.num;
			break;
		case EXPR_IDENT:
			if (!symbol_get(symbols, expr->as.ident, out))
			{
				fprintf(stderr, "Mather: Error: Undeffined variable \"%s\"\n", expr->as.ident);
				expr_free(expr);
				symbol_table_free(symbols);
				return false;
			}
		case EXPR_BINARY:
			if (!eval_expr(expr->as.binary.left, symbols, out)) return false;
			if (!eval_expr(expr->as.binary.right, symbols, out)) return false;
	}
	return false;
}

bool
execute_stmt(struct stmt *stmt, struct symbol_table *symbols)
{
	/* TODO: switch on stmt->type:
	 * PRINT_STMT: evaluate stmt->as.print and print the value.
	 * ASSIGN_STMT: evaluate stmt->as.assign.value, then call symbol_set.
	 * EXPR_STMT: evaluate stmt->as.expr and discard the result.
	 */
	(void)stmt;
	(void)symbols;
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
