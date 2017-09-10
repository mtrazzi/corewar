/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 14:49:35 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/09/10 15:05:01 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static	t_prc	*new_prc_lfork(t_env *e, t_prc *prc, int new_pc)
{
	t_prc	*new_prc;
	int		i;

	if (!(new_prc = (t_prc *)malloc(sizeof(t_prc))))
		return (NULL);
	i = 0;
	while (i++ < REG_NUMBER)
		new_prc->r[i] = prc->r[i];
	new_prc->pc = new_pc;
	new_prc->carry = prc->carry;
	new_prc->live = prc->live;
	new_prc->live_nb = prc->live_nb;
	new_prc->id = ++(e->last_id);
	new_prc->cyc_left = 0;
	new_prc->op_code = NB_OP + 1;
	new_prc->cyc_last_live = prc->cyc_last_live;
	return (new_prc);
}

int				lfork(t_env *e, t_prc *prc)
{
	int		addr_to_fork;
	int		addr_after_mod;
	t_prc	*new_prc;

	addr_to_fork = get_index(e, DIR_CODE, prc, prc->pc + 1);
	addr_after_mod = mod_map(prc->pc + addr_to_fork);
	if (!(new_prc = new_prc_lfork(e, prc, addr_after_mod)))
		return (ft_error_vm(STR_ERR_MALLOC_PRC));
	dll_push_front(&e->prc_lst, dll_new(new_prc));
	if (e->par.verb & V_4)
		printf("P %4d | lfork %d (%d)\n", prc->id,
		addr_to_fork, prc->pc + addr_to_fork);
	return (0);
}
