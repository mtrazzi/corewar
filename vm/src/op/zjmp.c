/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 14:59:04 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/11/06 20:11:47 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	zjmp(t_env *e, t_prc *prc)
{
	short index;

	index = (short)get_index(e, T_IND, prc, mod_map(prc->pc + 1));
	if (e->par.opts & OPT_V4)
		ft_printf("P %4d | zjmp %d ", prc->id, index);
	if (prc->carry)
	{
		prc->pc = mod_map(prc->pc + (index % IDX_MOD));
		if (e->par.opts & OPT_V4)
			ft_printf("OK\n");
	}
	else if (e->par.opts & OPT_V4)
		ft_printf("FAILED\n");
	return (0);
}
