/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 18:54:50 by pkirsch           #+#    #+#             */
/*   Updated: 2017/09/28 18:55:30 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

u_int		convert_op_code(u_int op_code)
{
	u_int	result;

	result = 1;
	while (op_code-- > 1)
		result <<= 1;// result *= 2;
	return (result);

	//result <<= op_code - 1;
}

static	int	count_types(t_ope *ope, u_char type)
{
	int		sum;
	int		i;

	sum = 0;
	i = -1;
	while (++i < MAX_ARGS_NUMBER)//ope->nb_param
	{
		if (ope->type_param[i] & type)
			sum++;
	}
	return (sum);
}

int			nb_bytes_op(t_ope *ope)
{
	int		sum;
	u_char	pcb;

	sum = 0;
	sum += count_types(ope, T_DIR) * (4 - 2 * ope->op_tab_x->label_size);//macros ?
	sum += count_types(ope, T_IND) * PAR_SIZE_IND;
	sum += count_types(ope, T_REG) * PAR_SIZE_REG;
	if (ope->op_tab_x->ocp)
	{
		sum += ope->op_tab_x->ocp > 0;
		pcb = calculate_pcb(ope);//ailleurs
		ope->ocp = pcb;
	}
	ope->size = sum + 1;
	return (1);
}

int		calc_add_size(t_dll *dll)
{
	if (dll->prev == NULL)
		((t_ope *)dll->content)->ais = 0;
	else
		((t_ope *)dll->content)->ais =
			 ((t_ope *)dll->prev->content)->ais
			 	+ ((t_ope *)dll->prev->content)->size;
	return (1);
}
