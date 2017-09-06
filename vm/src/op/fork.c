#include "vm.h"

static t_prc *new_prc_fork(t_env *e, t_prc *prc, int new_pc)
{
	t_prc	*new_prc;
	int		i;

	if (!(new_prc = (t_prc *)malloc(sizeof(t_prc))))
		return (NULL);
	i = 0;
	while (i++ < 16)
		new_prc->r[i] = prc->r[i];
	new_prc->pc = new_pc;
	new_prc->carry = prc->carry;
	new_prc->live = prc->live;
	new_prc->live_nb = prc->live_nb;
	new_prc->id = ++(e->last_id);
	new_prc->cyc_left = 0;
	new_prc->op_code = NB_OP + 1;
	new_prc->newly_created = 1;
	return (new_prc);
}

int     ft_fork(t_env *e, t_prc *prc)
{
	int	addr_to_fork;
	int addr_after_mod;
	t_prc *new_prc;

	addr_to_fork = get_index(e, DIR_CODE, prc, prc->pc + 1);
	addr_after_mod = prc->pc + (addr_to_fork % IDX_MOD);
	if (!(new_prc = new_prc_fork(e, prc, addr_after_mod)))
		return (ft_error_vm(STR_ERR_MALLOC_PRC));
	dll_push_front(&e->prc_lst, dll_new(new_prc));
	if (e->par.verb & V_4)
		ft_printf("P%5d | fork %d (%d)\n", prc->id, addr_to_fork, addr_after_mod);
    return (0);
}
