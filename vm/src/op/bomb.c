/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bomb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 18:50:07 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/09/10 18:50:10 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	bomb(t_env *e, t_prc *prc)
{
	short index;

	index = (short)get_index(e, T_IND, prc, mod_map(prc->pc + 1));
	if (e->par.verb & V_4)
		printf("P %4d | throwing a bomb and jumping at %d\n", prc->id, index);
	prc->pc = mod_map(prc->pc + (index % IDX_MOD));
	if (e->cyc > 2)
		e->cyc /= 2;
	return (0);
}
