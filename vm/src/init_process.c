/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 11:49:01 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/09/10 11:54:35 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	init_reg(t_prc *prc)
{
	int i;

	i = 0;
	while (i < REG_NUMBER)
		prc->r[i++] = 0;
}

t_prc		*new_prc(u_int pc, int nb, int id)
{
	t_prc *prc;

	if (!(prc = (t_prc *)malloc(sizeof(t_prc))))
		return (NULL);
	init_reg(prc);
	prc->r[1] = nb;
	prc->pc = pc;
	prc->carry = 0;
	prc->live = 0;
	prc->live_nb = 0;
	prc->id = id;
	prc->cyc_left = 0;
	prc->op_code = NB_OP + 1;
	prc->cyc_last_live = 0;
	return (prc);
}

int			init_all_processes(t_env *e)
{
	u_int i;
	t_prc *prc;

	i = 0;
	while (i < e->par.nb_chp)
	{
		if (!(prc = new_prc((MEM_SIZE / e->par.nb_chp) * i,
								e->par.champions[i].nb, i + 1)))
			return (ft_error_vm(STR_ERR_MALLOC_PRC));
		if (e->par.print)
			e->map_color[mod_map((MEM_SIZE / e->par.nb_chp) * i)].is_prc = 1;
		dll_push_front(&e->prc_lst, dll_new(prc));
		i++;
	}
	e->last_id = e->par.nb_chp;
	return (0);
}
