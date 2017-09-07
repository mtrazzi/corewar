#include "vm.h"

int		live(t_env *e, t_prc *prc)
{
	int ret;

	prc->live += 1;
	prc->live_nb = get_value(e, DIR_CODE, prc, prc->pc + 1);
	e->nb_live += 1;
	if (e->par.verb & V_4)
		ft_printf("P%5d | live %d\n", prc->id, prc->live_nb);
	if ((ret = is_real_number(e, prc->live_nb)) > 0)
	{
		prc->cyc_last_live = e->cyc_since_beg;
		e->last_alive = prc->live_nb;
		if (e->par.verb & V_1)
			ft_printf("Player %d (%s) is said to be alive\n", ret, e->par.champions[ret - 1].name);
	}
	return (0);
}
