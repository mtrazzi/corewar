/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nand.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 18:03:01 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/09/10 18:03:08 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

#define OP_NAND 19

int	nand(t_env *e, t_prc *prc)
{
	u_char	ocp;
	int		params[4];
	int		offset;
	int		reg_nb;

	offset = 1;
	ocp = e->map[mod_map(prc->pc + offset)];
	offset += 1;
	params[1] = get_value(e, (ocp >> 6) % 4, prc, mod_map(prc->pc + offset));
	offset += sizeof_param(OP_NAND, (ocp >> 6) % 4);
	params[2] = get_value(e, (ocp >> 4) % 4, prc, mod_map(prc->pc + offset));
	offset += sizeof_param(OP_NAND, (ocp >> 4) % 4);
	reg_nb = e->map[mod_map(prc->pc + offset)];
	prc->r[reg_nb] = ~(params[1] & params[2]);
	prc->carry = prc->r[reg_nb] == 0;
	if (e->par.verb & V_4)
		printf("P %4d | nand %d %d r%d\n", prc->id, params[1], params[2],
				reg_nb);
	return (0);
}
