#include "vm.h"

int     sub(t_env *e, t_prc *prc)
{
	int		nb_1;
	int		nb_2;
	int		nb_3;

	nb_1 = e->map[(prc->pc + 2) % MEM_SIZE];
	nb_2 = e->map[(prc->pc + 3) % MEM_SIZE];
	nb_3 = e->map[(prc->pc + 4) % MEM_SIZE];
	prc->r[nb_3] = prc->r[nb_1] - prc->r[nb_2];
	prc->carry = (prc->r[nb_3] == 0);
	if (e->par.verb & V_4)
		ft_printf("P    %d | sub r%d r%d r%d\n", prc->id, nb_1, nb_2, nb_3);
    return (0);
}
