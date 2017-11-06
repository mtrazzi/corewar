/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 18:54:50 by pkirsch           #+#    #+#             */
/*   Updated: 2017/09/29 17:45:40 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**	MAX_ARGS_NUMBER
*/

static int		count_types(t_ope *ope, u_char type)
{
	int		sum;
	u_int	i;

	sum = 0;
	i = 0;
	while (i < ope->nb_param)
	{
		if (ope->type_param[i] & type)
			sum++;
		++i;
	}
	return (sum);
}

static u_char	calculate_pcb(t_ope *ope)
{
	int		i;
	u_char	result;

	result = 0;
	i = -1;
	while (++i < MAX_ARGS_NUMBER)
	{
		if (ope->type_param[i] & T_REG)
			result |= REG_CODE << (3 - i) * 2;
		else if (ope->type_param[i] & T_DIR)
			result |= DIR_CODE << (3 - i) * 2;
		else if (ope->type_param[i] & T_IND)
			result |= IND_CODE << (3 - i) * 2;
		else
			break ;
	}
	return (result);
}

/*
**	and calculate ocp
*/

int				nb_bytes_op(t_ope *ope)
{
	int		sum;
	u_char	pcb;

	sum = 0;
	sum += count_types(ope, T_DIR) * (4 - 2 * ope->op_tab_x->label_size);
	sum += count_types(ope, T_IND) * PAR_SIZE_IND;
	sum += count_types(ope, T_REG) * PAR_SIZE_REG;
	if (ope->op_tab_x->ocp)
	{
		sum += ope->op_tab_x->ocp > 0;
		pcb = calculate_pcb(ope);
		ope->ocp = pcb;
	}
	ope->size = sum + 1;
	return (1);
}

int				calc_add_size(t_dll *dll)
{
	if (dll->prev == NULL)
		((t_ope *)dll->content)->ais = 0;
	else
		((t_ope *)dll->content)->ais =
			((t_ope *)dll->prev->content)->ais
				+ ((t_ope *)dll->prev->content)->size;
	return (1);
}
