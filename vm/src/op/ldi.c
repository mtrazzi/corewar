/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 14:49:33 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/09/10 15:05:24 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

#define OP_LDI 10

int	ldi(t_env *e, t_prc *prc)
{
	u_char	ocp;
	int		params[4];
	int		offset;
	int		addr;

	ocp = e->map[mod_map(prc->pc + 1)];
	offset = 2;
	if (((ocp >> 6) % 4) == DIR_CODE)
		params[1] = get_index(e, (ocp >> 6) % 4, prc, prc->pc + offset);
	if (((ocp >> 6) % 4) == IND_CODE)
		params[1] = get_value(e, (ocp >> 6) % 4, prc, prc->pc + offset);
	offset += sizeof_param(OP_LDI, (ocp >> 6) % 4);
	params[2] = get_index(e, (ocp >> 4) % 4, prc, prc->pc + offset);
	offset += sizeof_param(OP_LDI, (ocp >> 4) % 4);
	addr = prc->pc + (params[1] + params[2]) % IDX_MOD;
	prc->r[e->map[mod_map(prc->pc + offset)]] = get_value(e, DIR_CODE, prc,
																		addr);
	if (e->par.opts & OPT_V4)
	{
		printf("P %4d | ldi %d %d r%d\n", prc->id, params[1], params[2],
		e->map[mod_map(prc->pc + offset)]);
		printf("       | -> load from %d + %d = %d (with pc and mod %d)\n", \
		params[1], params[2], params[1] + params[2], addr);
	}
	return (0);
}
