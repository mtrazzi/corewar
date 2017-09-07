#include "vm.h"

int     aff(t_env *e, t_prc *prc)
{
	unsigned char c;

	c = (unsigned char)get_value(e, REG_CODE, prc, prc->pc + 2);
	//printf("%c", c);
    return (0);
}
