/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 11:44:59 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/09/10 11:46:55 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

#define DEBUG_CHECK_PARAMS 0

static	int		is_reg(t_env *e, int pos)
{
	int reg_nb;

	reg_nb = e->map[mod_map(pos)];
	return (reg_nb > 0 && reg_nb <= REG_NUMBER);
}

static	int		are_param_correct(t_env *e, t_prc *prc, u_char ocp,
														u_int op_code)
{
	u_int	tmp;
	u_int	max;
	u_int	i;
	int		offset;

	max = g_op_tab[op_code - 1].nb_param + 1;
	i = 0;
	offset = 2;
	while (++i < max)
	{
		tmp = (ocp >> (4 - i) * 2) & LAST_TWO_BITS;
		if ((g_op_tab[op_code - 1].type_param[i - 1] &
			(tmp == IND_CODE ? T_IND : tmp)) == 0)
			return (0);
		if (tmp == REG_CODE && !is_reg(e, prc->pc + offset))
			return (0);
		offset += sizeof_param(op_code, tmp);
	}
	return (1);
}

int				check_params(t_env *e, t_prc *prc, int op_code)
{
	u_char	ocp;

	if (!(g_op_tab[op_code - 1].ocp))
		return (1);
	ocp = e->map[mod_map(prc->pc + 1)];
	return (are_param_correct(e, prc, ocp, op_code));
}
