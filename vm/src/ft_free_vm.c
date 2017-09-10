#include "vm.h"

int ft_free_vm_env(t_env *e)
{
	if (e->prc_lst)
		dll_del_f(&e->prc_lst, &free);
	return (1);
}
