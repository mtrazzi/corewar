/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 12:26:46 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/09/10 13:16:30 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

#define PAR_SIZE_REG 1
#define PAR_SIZE_IND 2

u_int	mod_map(int nbr)
{
	while (nbr < 0)
		nbr += MEM_SIZE;
	return (nbr % MEM_SIZE);
}

int		sizeof_param(u_char op_code, u_char type_of_param)
{
	if (type_of_param == REG_CODE)
		return (PAR_SIZE_REG);
	else if (type_of_param == IND_CODE)
		return (PAR_SIZE_IND);
	else if (type_of_param == DIR_CODE)
		return (4 - 2 * (g_op_tab[op_code - 1].last_arg));
	return (0);
}

int		nb_bytes_to_skip(u_char op_code, u_char ocp)
{
	int		sum;
	u_int	i;

	if (!(g_op_tab[op_code - 1].ocp))
		return (1 + (op_code == 1 ? 4 : 2));
	sum = 2;
	i = 0;
	while (++i <= g_op_tab[op_code - 1].nb_param)
		sum += sizeof_param(op_code, (ocp >> (4 - i) * 2) & LAST_TWO_BITS);
	return (sum);
}

int		get_value(t_env *e, u_char type_of_param, t_prc *prc, u_int pos)
{
	int index;
	int addr;

	if (type_of_param == REG_CODE)
		return (prc->r[e->map[mod_map(pos)]]);
	else if (type_of_param == DIR_CODE)
	{
		return (convert_4_bytes(e->map[mod_map(pos + 0)],
								e->map[mod_map(pos + 1)],
								e->map[mod_map(pos + 2)],
								e->map[mod_map(pos + 3)]));
	}
	index = convert_2_bytes(e->map[mod_map(pos)], e->map[mod_map(pos + 1)]);
	addr = prc->pc + (index % IDX_MOD);
	return (convert_4_bytes(e->map[mod_map(addr + 0)],
				e->map[mod_map(addr + 1)],
				e->map[mod_map(addr + 2)],
				e->map[mod_map(addr + 3)]));
}

int		lget_value(t_env *e, u_char type_of_param, t_prc *prc, u_int pos)
{
	int index;
	int addr;

	if (type_of_param == REG_CODE)
		return (prc->r[e->map[mod_map(pos)]]);
	else if (type_of_param == DIR_CODE)
	{
		return (convert_4_bytes(e->map[mod_map(pos + 0)],
				e->map[mod_map(pos + 1)],
				e->map[mod_map(pos + 2)],
				e->map[mod_map(pos + 3)]));
	}
	index = convert_2_bytes(e->map[mod_map(pos)], e->map[mod_map(pos + 1)]);
	addr = prc->pc + index;
	return (convert_4_bytes(e->map[mod_map(addr + 0)],
				e->map[mod_map(addr + 1)],
				e->map[mod_map(addr + 2)],
				e->map[mod_map(addr + 3)]));
}
