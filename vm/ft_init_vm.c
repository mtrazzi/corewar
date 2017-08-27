#include "vm.h"

int		ft_init_vm(t_env *e)
{
	ft_bzero(e->map, MEM_SIZE);
	e->prc_lst = NULL;
	e->cyc = 0;
	e->nb_live = 0;
	return (1);
}
