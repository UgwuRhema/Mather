#ifndef MATHER_SYMBOL_H
#define MATHER_SYMBOL_H

#include <stdbool.h>
#include <stddef.h>

struct symbol
{
	char *name;
	int value;
	struct symbol *next;
};

struct symbol_table
{
	struct symbol *head;
	size_t count;
};

/* TODO: implement the functions below in symbol.c. */

/* TODO: allocate an empty table; return NULL on allocation failure. */
struct symbol_table *symbol_table_new(void);

/* TODO: free every symbol, each symbol's name, then the table itself. */
void symbol_table_free(struct symbol_table *table);

/* TODO: create the symbol if missing, update it if present, and copy name.
 * Return false on allocation failure.
 */
bool symbol_set(struct symbol_table *table, const char *name, int value);

/* TODO: copy the symbol's value into *value.
 * Return false if the symbol does not exist.
 */
bool symbol_get(const struct symbol_table *table, const char *name, int *value);

#endif
