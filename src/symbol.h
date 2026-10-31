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

struct symbol_table *symbol_table_new(void);
void symbol_table_free(struct symbol_table *);
bool symbol_set(struct symbol_table *, const char *, int);
bool symbol_get(const struct symbol_table *, const char *, int *);

#endif
