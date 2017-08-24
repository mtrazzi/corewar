#include "asm.h"

t_asm	*ft_init_asm(void)
{
	t_asm	*e;

	e = (t_asm *)ft_memalloc(sizeof(t_asm));
	e->lst = NULL;
	e->fd = 0;
	return (e);
}
