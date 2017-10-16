/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 14:58:53 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/09/10 15:44:35 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

#define OP_ST 3

int	st(t_env *e, t_prc *prc)
{
	u_char	ocp;
	int		params[4];
	int		offset;

	ocp = e->map[mod_map(prc->pc + 1)];
	params[1] = prc->r[e->map[mod_map(prc->pc + 2)]];
	offset = 3;
	if (((ocp >> 4) % 4) == IND_CODE)
	{
		params[2] = get_index(e, (ocp >> 4) % 4, prc, prc->pc + offset);
		if (e->par.verb & V_4)
			printf("P %4d | st r%d %d\n", prc->id,
			e->map[mod_map(prc->pc + 2)], params[2]);
		copy_value(params[1], e, mod_map(prc->pc + (params[2] % IDX_MOD)), get_color(e, prc->r[1]));
		return (0);
	}
	else if (((ocp >> 4) % 4) == REG_CODE)
		prc->r[e->map[mod_map(prc->pc + offset)]] = params[1];
	if (e->par.verb & V_4)
	{
		printf("P %4d | st r%d %d\n", prc->id, e->map[mod_map(prc->pc + 2)],
				e->map[mod_map(prc->pc + offset)]);
	}
	return (0);
}
