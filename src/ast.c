#include "ast.h"
#include <stdlib.h>

struct expr *
expr_num(int value)
{
	struct expr *ne = (struct expr *)malloc(sizeof(struct expr));	
	ne->type = EXPR_NUM;
	ne->as.num = value;
	return ne;
}
