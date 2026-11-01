#ifndef MATHER_EXE_H
#define MATHER_EXE_H

#include <stdbool.h>
#include "ast.h"
#include "symbol.h"

bool eval_expr(struct expr *expr, struct symbol_table *symbols, int *out);
bool execute_stmt(struct stmt *stmt, struct symbol_table *symbols);
bool execute_tree(struct tree *tree);

#endif
