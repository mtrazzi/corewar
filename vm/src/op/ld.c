/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 14:49:30 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/09/10 14:49:32 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

#define OP_LD 2

int	ld(t_env *e, t_prc *prc)
{
	u_char	ocp;
	int		params[4];
	int		offset;
	int		reg_nb;

	offset = 1;
	ocp = e->map[mod_map(prc->pc + offset)];
	offset += 1;
	params[1] = get_value(e, (ocp >> 6) % 4, prc, mod_map(prc->pc + offset));
	offset += sizeof_param(OP_LD, (ocp >> 6) % 4);
	reg_nb = e->map[mod_map(prc->pc + offset)];
	prc->r[reg_nb] = params[1];
	prc->carry = prc->r[reg_nb] == 0;
	if (e->par.verb & V_4)
		printf("P %4d | ld %d r%d\n", prc->id, params[1], reg_nb);
	return (0);
}
