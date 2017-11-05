/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bomb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 18:50:07 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/11/05 23:17:35 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	bomb(t_env *e, t_prc *prc)
{
	short index;

	index = (short)get_index(e, T_IND, prc, mod_map(prc->pc + 1));
	if (e->par.opts & OPT_V4)
		printf("P %4d | throwing a bomb and jumping at %d ", prc->id, index);
	if (prc->carry)
	{
		prc->pc = mod_map(prc->pc + (index % IDX_MOD));
		if (e->par.opts & OPT_V4)
			printf("BAOOOOMMMMMMMM\n");
	}
	else if (e->par.opts & OPT_V4)
		printf("Bomb has been defused\n");
	if (e->cyc > 2)
		e->cyc /= 2;
	return (0);
}
