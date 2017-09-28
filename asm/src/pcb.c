/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pcb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 19:08:27 by pkirsch           #+#    #+#             */
/*   Updated: 2017/09/28 18:49:53 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

u_char	calculate_pcb(t_ope *ope)
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
