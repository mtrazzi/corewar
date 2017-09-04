#include "vm.h"

int     zjmp(t_env *e, t_prc *prc)
{
	short index;

	index = (short)get_index(e, T_IND, prc, (prc->pc + 1) % MEM_SIZE);
	if (e->par.verb & V_4)
		ft_printf("P    %d | zjmp %d ", prc->id, index);
	// while (index < 0)			//problem when modulo with negative n	b
	// 	index += IDX_MOD;
	if (prc->carry)
	{
		prc->pc = (prc->pc + (index % IDX_MOD)) % MEM_SIZE;
		if (e->par.verb & V_4)
			ft_printf("OK\n");
	}
	else if (e->par.verb & V_4)
		ft_printf("FAILED\n");
    return (0);
}
