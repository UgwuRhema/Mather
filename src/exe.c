#include "exe.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

bool
eval_expr(struct expr *expr, struct symbol_table *symbols, double *out)
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
			double left, right;
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
				case OP_GTHAN:
					if (left > right)
						*out = 1.0;/*true*/
					else
						*out = 0.0;/*false*/
					break;
				case OP_LTHAN:
					if (left < right)
						*out = 1.0;
					else
						*out = 0.0;
					break;
				case OP_EXEQ:
					if (left == right)
						*out = 1.0;
					else
						*out = 0.0;
					break;
				default:
					return false;
			}
			return true;
		default:
			return false;
		case EXPR_INPUT:
		{
			char buffer[256];
			char *end;
			if (!fgets(buffer, sizeof(buffer), stdin))
			{
				fprintf(stderr, "Mather: Error: Failed to read input\n");
				return false;
			}
			*out = strtod(buffer, &end);
			if (end ==  buffer)
			{
				fprintf(stderr, "Mather: Error: Invalid numeric input\n");
				return false;
			}
			return true;
		}
        case EXPR_CALL:
        {
            if (strcmp(expr->as.call.name, "sqrt") == 0)
            {
                if (expr->as.call.argc != 1)
                {
                    fprintf(stderr, "Mather: Error: sqrt() function needs 1 argument\n");
					return false;
				}
				double number;
				if (!eval_expr(*expr->as.call.args->items, symbols, &number))
				{
					fprintf(stderr, "Mather: Error: Failed to evaluate expression in sqrt() function\n");
					return false;
				}
				*out = sqrt(number);
				return true;
            } else if (strcmp(expr->as.call.name, "pow") == 0) {
				if (expr->as.call.argc != 2)
					return false;
				/*numbers for the base and number*/
				double base = 0.0;
				double power = 0.0;
				if (!eval_expr(expr->as.call.args->items[0], symbols, &base))
				{
					fprintf(stderr, "Mather: Error: Couldn't parse expressions in pow function\n");
					return false;
				}
				if (!eval_expr(expr->as.call.args->items[1], symbols, &power))
				{
					fprintf(stderr, "Mather: Error: Couldn't parse expressions in pow function\n");
					return false;
				}
				/*debug*/
				*out = pow(base, power);
				return true;
			} else if (strcmp(expr->as.call.name, "round") == 0) {
				if (expr->as.call.argc != 1)
					return false;
				double number = 0.0;
				bool res = eval_expr(expr->as.call.args->items[0], symbols, &number);
				if (!res)
					return false;
				*out = round(number);
				return true;
			} else if (strcmp(expr->as.call.name, "ceil") == 0) {
				if (expr->as.call.argc != 1)
					return false;
				double number = 0.0;
				bool res = eval_expr(expr->as.call.args->items[0], symbols, &number);
				if (!res)
					return false;
				*out = ceil(number);
				return true;
			}
			return false;
        }
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
			double out;
			if (!eval_expr(stmt->as.print, symbols, &out))
			{
				fprintf(stderr, "Mather: Error: Failed to evaluate the expression\n");
				return false;
			}
			printf("%g\n", out);
			return true;
		case PRINT_STRING_STMT:
			if (stmt->as.print_str != NULL) {
				printf("%s", stmt->as.print_str);
				return true;
			}
			return false;
		case ASSIGN_STMT:
			double out2;
			if (!eval_expr(stmt->as.assign.value, symbols, &out2))
			{
				fprintf(stderr, "Mather: Error: Failed to evaluate the expression\n");
				return false;
			}
			/*add to symbol table so we can keep track of variables*/
			if (!symbol_set(symbols, stmt->as.assign.name, out2))
			{
				fprintf(stderr, "Mather: Error: Unable to assign value to variable\n");
				return false;
			}
			return true;
		case EXPR_STMT:
			double out3;
			if (!eval_expr(stmt->as.expr, symbols, &out3))
			{
				fprintf(stderr, "Mather: Error: Failed to evaluate the expression\n");
				return false;
			}
			/*we don't use value*/
			return true;
		case CONDITION_STMT:
			double out4;/*this would hold the condition expression
			which is either 1 or 0*/
			if (!eval_expr(stmt->as.condition.condition, symbols, &out4))
			{
				fprintf(stderr, "Mather: Error: Failed to evaluate expression in conditional statement\n");
				return false;
			}
			/*DEBUG*/
			printf("Value: %g\n", out4);
			if (out == 1.0)/*if the condition is true, we execute it*/
			{
				if (!execute_tree(stmt->as.condition.head))
				{
					fprintf(stderr, "Mather: Error: Failed to execute statements in conditional statement\n");
					return false;
				}
			} else if (out == 0.0) { /*else we don't*/
				return true;
			} else {
				fprintf(stderr, "Mather: fatal error: Unknown expression result for conditional statement\n");
				abort();
			}
			return true;
		default:
			return false;
	}
	return false;
}

bool
execute_tree(struct tree *tree)
{
	if (!tree) return false;
	struct symbol_table *sym = symbol_table_new();
	if (!sym)
		return false;
	tree->statements = reverse_stmt_list(tree);/*reverse the statement list*/
	struct stmt *curr_stmt = tree->statements;
	while (curr_stmt)
	{
		if (!execute_stmt(curr_stmt, sym))
		{
			fprintf(stderr, "Mather: Error: Failed to execute statement\n");
			return false;
		}
		curr_stmt = curr_stmt->next;
	}
	symbol_table_free(sym);
	return true;
}
