/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laranda <laranda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 14:58:53 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/11/05 18:46:24 by laranda          ###   ########.fr       */
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
		if (e->par.opts & OPT_V4)
			ft_printf("P %4d | st r%d %d\n", prc->id,
					e->map[mod_map(prc->pc + 2)], params[2]);
		copy_value(params[1], e, mod_map(prc->pc + (params[2] % IDX_MOD)),
					get_color(e, prc->chp_nb));
		return (0);
	}
	else if (((ocp >> 4) % 4) == REG_CODE)
		prc->r[e->map[mod_map(prc->pc + offset)]] = params[1];
	if (e->par.opts & OPT_V4)
	{
		ft_printf("P %4d | st r%d %d\n", prc->id, e->map[mod_map(prc->pc + 2)],
				e->map[mod_map(prc->pc + offset)]);
	}
	return (0);
}
