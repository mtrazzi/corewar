/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 14:59:02 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/11/02 20:27:20 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

#define OP_XOR 8

int	xor(t_env *e, t_prc *prc)
{
	u_char	ocp;
	int		params[4];
	int		offset;
	int		reg_nb;

	offset = 1;
	ocp = e->map[mod_map(prc->pc + offset)];
	offset += 1;
	params[1] = get_value(e, (ocp >> 6) % 4, prc, mod_map(prc->pc + offset));
	offset += sizeof_param(OP_XOR, (ocp >> 6) % 4);
	params[2] = get_value(e, (ocp >> 4) % 4, prc, mod_map(prc->pc + offset));
	offset += sizeof_param(OP_XOR, (ocp >> 4) % 4);
	reg_nb = e->map[mod_map(prc->pc + offset)];
	prc->r[reg_nb] = params[1] ^ params[2];
	prc->carry = prc->r[reg_nb] == 0;
	if (e->par.opts & OPT_V4)
		ft_printf("P %4d | xor %d %d r%d\n",
		prc->id, params[1], params[2], reg_nb);
	return (0);
}
