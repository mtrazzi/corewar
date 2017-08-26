#include "asm.h"

int		ft_init_asm(t_asm *e)
{
	e->lst = NULL;
	e->header = NULL;
	e->fd = 0;
	return (1);
}
