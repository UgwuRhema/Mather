#include "exe.h"

bool
eval_expr(struct expr *expr, struct symbol_table *symbols, int *out)
{
	/* TODO: switch on expr->type:
	 * EXPR_NUM: assign expr->as.num to *out.
	 * EXPR_IDENT: use symbol_get with expr->as.ident.
	 * EXPR_BINARY: evaluate left and right, then apply expr->as.binary.op.
	 */
	(void)expr;
	(void)symbols;
	(void)out;
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
