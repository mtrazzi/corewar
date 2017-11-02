/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 14:58:56 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/11/02 20:27:24 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

#define OP_STI 11
#define DEBUG_STI 1

int	sti(t_env *e, t_prc *prc)
{
	u_char	ocp;
	int		params[4];
	int		offset;
	int		addr;

	ocp = e->map[mod_map(prc->pc + 1)];
	offset = 2;
	params[1] = prc->r[e->map[mod_map(prc->pc + offset)]];
	offset += 1;
	if (((ocp >> 4) % 4) == DIR_CODE)
		params[2] = get_index(e, (ocp >> 4) % 4, prc, prc->pc + offset);
	else
		params[2] = get_value(e, (ocp >> 4) % 4, prc, prc->pc + offset);
	offset += sizeof_param(OP_STI, (ocp >> 4) % 4);
	params[3] = get_index(e, (ocp >> 2) % 4, prc, prc->pc + offset);
	addr = prc->pc + (params[2] + params[3]) % IDX_MOD;
	if (e->par.opts & OPT_V4)
	{
		printf("P %4d | sti r%d %d %d\n", prc->id, e->map[mod_map(prc->pc + 2)],
		params[2], params[3]);
		printf("       | -> store to %d + %d = %d (with pc and mod %d)\n",
		params[2], params[3], params[2] + params[3], addr);
	}
	copy_value(params[1], e, mod_map(addr), get_color(e, prc->r[1]));
	return (0);
}
