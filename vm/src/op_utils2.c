/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 12:23:01 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/09/10 12:26:40 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	copy_value(int value, t_env *e, u_int pos, u_char color)
{
	e->map[mod_map(pos + 0)] = value >> 24;
	e->map[mod_map(pos + 1)] = ((value << 8) >> 24);
	e->map[mod_map(pos + 2)] = ((value << 16) >> 24);
	e->map[mod_map(pos + 3)] = ((value << 24) >> 24);
	e->map_color[mod_map(pos + 0)] = color;
	e->map_color[mod_map(pos + 1)] = color;
	e->map_color[mod_map(pos + 2)] = color;
	e->map_color[mod_map(pos + 3)] = color;
}

int		is_real_number(t_env *e, int nb)
{
	u_int i;

	i = 0;
	while (i < e->par.nb_chp)
	{
		if (e->par.champions[i].nb == nb)
			return (i + 1);
		i++;
	}
	return (0);
}

int		get_index(t_env *e, u_char type_of_param, t_prc *prc, u_int pos)
{
	if (type_of_param == REG_CODE)
		return (prc->r[e->map[mod_map(pos)]]);
	return (convert_2_bytes(e->map[mod_map(pos)], e->map[mod_map(pos + 1)]));
}

int	get_color(t_env *e, int nb)
{
	int i;
	t_chp chp;

	i = 0;
	while (i < e->par.nb_chp)
	{
		chp = e->par.champions[i];
		if (chp.nb == nb)
			return (2 * i + 1);
		i++;
	}
}
