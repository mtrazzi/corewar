/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 14:49:41 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/09/10 15:10:54 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

#define OP_LLDI 14

int	lldi(t_env *e, t_prc *prc)
{
	u_char	ocp;
	int		params[4];
	int		offset;
	int		addr;

	ocp = e->map[mod_map(prc->pc + 1)];
	if (((ocp >> 6) % 4) == DIR_CODE)
		params[1] = get_index(e, (ocp >> 6) % 4, prc, prc->pc + 2);
	if (((ocp >> 6) % 4) == IND_CODE)
		params[1] = lget_value(e, (ocp >> 6) % 4, prc, prc->pc + 2);
	offset = 2 + sizeof_param(OP_LLDI, (ocp >> 6) % 4);
	params[2] = get_index(e, (ocp >> 4) % 4, prc, prc->pc + offset);
	offset += sizeof_param(OP_LLDI, (ocp >> 4) % 4);
	addr = prc->pc + (params[1] + params[2]);
	prc->r[e->map[mod_map(prc->pc + offset)]] = lget_value(e, DIR_CODE, prc,
																		addr);
	prc->carry = (lget_value(e, DIR_CODE, prc, addr) == 0);
	if (e->par.verb & V_4)
	{
		printf("P %4d | lldi %d %d r%d\n", prc->id, params[1], params[2],
		e->map[mod_map(prc->pc + offset)]);
		printf("       | -> load from %d + %d = %d (with pc %d)\n", \
		params[1], params[2], params[1] + params[2], addr);
	}
	return (0);
}
