#include "symbol.h"
#include <stdlib.h>
#include <string.h>

struct symbol_table *
symbol_table_new(void)
{
	struct symbol_table *nst = (struct symbol_table *)malloc(sizeof(struct symbol_table));
	if (!nst)
		return NULL;
	nst->head = NULL;
	nst->count = 0;
	return nst;
}

void 
symbol_table_free(struct symbol_table *table)
{
	if (!table)
		return;
	struct symbol *curr = table->head;
	while (curr)
	{
		struct symbol *next = curr->next;
		free((void *)curr->name);
		free((void *)curr);
		curr = next;
	}
	free((void *)table);
}

bool
symbol_set(struct symbol_table *table, const char *name, int value)
{
	if (!table || !name) return false;
	struct symbol *curr = table->head;
	/*lookup*/
	while (curr)
	{
		if (strcmp(name, curr->name) == 0)
		{
			curr->value = value;
			return true;
		}
		curr = curr->next;
	}
	struct symbol *sym = (struct symbol *)malloc(sizeof(struct symbol));
	if (!sym) return false;
	sym->value = value;
	sym->name = strdup(name);
	if (!sym->name)
	{
		free((void *)sym);
		return false;
	}
	sym->next = table->head;
	table->head = sym;
	table->count++;
	return true;
}

bool
symbol_get(const struct symbol_table *st, const char *k, int *val)
{
	if (!st || !k) return false;
	/*another lookup*/
	struct symbol *curr = st->head;
	while (curr)
	{
		if (strcmp(k, curr->name) == 0)
		{
			/*we found it*/
			*val = curr->value;
			return true;
		}
		curr = curr->next;
	}
	return false;
}
