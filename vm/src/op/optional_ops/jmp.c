/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 18:49:50 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/09/10 18:49:55 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	jmp(t_env *e, t_prc *prc)
{
	short index;

	index = (short)get_index(e, T_IND, prc, mod_map(prc->pc + 1));
	if (e->par.opts & OPT_V4)
		printf("P %4d | jmp %d\n", prc->id, index);
	prc->pc = mod_map(prc->pc + (index % IDX_MOD));
	return (0);
}
