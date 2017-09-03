#include "vm.h"

int     zjmp(t_env *e, t_prc *prc)
{
	short index;

	index = (short)get_index(e, T_IND, prc, (prc->pc + 1) % MEM_SIZE);
	ft_printf("P    %d | zjmp %d ", prc->id, index);
	if (prc->carry)
	{
		prc->pc = (prc->pc + (index % IDX_MOD)) % MEM_SIZE;
		ft_printf("OK\n");
	}
	else
		ft_printf("FAILED\n");
    return (0);
}
