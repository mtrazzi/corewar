/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 14:59:04 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/09/10 14:59:07 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	zjmp(t_env *e, t_prc *prc)
{
	short index;

	index = (short)get_index(e, T_IND, prc, mod_map(prc->pc + 1));
	if (e->par.verb & V_4)
		printf("P %4d | zjmp %d ", prc->id, index);
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
