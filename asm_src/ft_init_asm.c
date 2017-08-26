#include "asm.h"

t_asm	ft_init_asm(void)
{
	t_asm	e;

	e.lst = NULL;
	e.header = NULL;
	e.fd = 0;
	return (e);
}
