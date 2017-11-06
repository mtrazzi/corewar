/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 11:50:00 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/11/06 20:49:41 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

#define OP_ZJMP 0x09
#define OP_BOMB 0x16

#define STR_OP_ERROR ("Fatal operation error")

int		process_exec_op_update_cyc_left(t_env *e, t_prc *prc)
{
	int skip;

	prc->cyc_left -= 1;
	if ((prc->cyc_left == 0 && prc->op_code != NB_OP + 1))
	{
		skip = nb_bytes_to_skip(prc->op_code, e->map[mod_map(prc->pc + 1)]);
		if (check_params(e, prc, prc->op_code))
			if (g_op_fun_tab[prc->op_code - 1](e, prc) < 0)
				return (ft_error_vm(STR_OP_ERROR));
		if ((prc->op_code != OP_ZJMP && prc->op_code != OP_BOMB)
				|| !(prc->carry))
		{
			if (e->par.opts & OPT_V16)
				print_adv(e, prc->pc, skip);
			prc->pc = mod_map(prc->pc + skip);
		}
	}
	else if (prc->cyc_left == 0)
		prc->pc = mod_map(prc->pc + 1);
	return (0);
}

int		process_load_op(t_env *e, t_prc *prc)
{
	if (prc->cyc_left != 0)
		return (0);
	prc->op_code = e->map[mod_map(prc->pc)];
	if (prc->op_code == 0 || prc->op_code > NB_OP)
		prc->op_code = NB_OP + 1;
	prc->cyc_left = g_op_tab[prc->op_code - 1].nb_cycles;
	return (0);
}

int		do_process(t_env *e, t_prc *prc)
{
	if (e->par.opts & OPT_M)
		e->map_color[mod_map(prc->pc)].is_prc = 0;
	process_load_op(e, prc);
	if (process_exec_op_update_cyc_left(e, prc) < 0)
		return (-1);
	if (e->par.opts & OPT_M)
		e->map_color[mod_map(prc->pc)].is_prc = 1;
	return (1);
}
