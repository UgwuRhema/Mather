#ifndef MATHER_EXE_H
#define MATHER_EXE_H

#include <stdbool.h>
#include "ast.h"
#include "symbol.h"

/* TODO: evaluate expr into *out.
 * Return false for an undefined identifier or division by zero.
 */
bool eval_expr(struct expr *expr, struct symbol_table *symbols, int *out);

/* TODO: execute one statement.
 * PRINT_STMT: evaluate and print the expression.
 * ASSIGN_STMT: evaluate the value, then call symbol_set.
 * EXPR_STMT: evaluate and discard the result.
 */
bool execute_stmt(struct stmt *stmt, struct symbol_table *symbols);

/* TODO: execute the whole tree in source order.
 * Create the symbol table, reverse the statement list exactly once,
 * execute each statement, then free the symbol table.
 */
bool execute_tree(struct tree *tree);

#endif
