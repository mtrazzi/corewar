#include "vm.h"

int     zjmp(t_env *e, t_prc *prc)
{
	short index;

	index = (short)get_index(e, T_IND, prc, mod_map(prc->pc + 1));
	if (e->par.verb & V_4)
		printf("P %4d | zjmp %d ", prc->id, index);
	// while (index < 0)			//problem when modulo with negative n	b
	// 	index += IDX_MOD;
	if (prc->carry)
	{
		prc->pc = mod_map(prc->pc + (index % IDX_MOD));
		if (e->par.verb & V_4)
			printf("OK\n");
	}
	else if (e->par.verb & V_4)
		printf("FAILED\n");
    return (0);
}
