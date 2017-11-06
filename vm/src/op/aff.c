/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 14:49:21 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/11/05 19:16:42 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	aff(t_env *e, t_prc *prc)
{
	unsigned char c;

	c = (unsigned char)get_value(e, REG_CODE, prc, prc->pc + 2);
	if (e->par.opts & OPT_A)
		ft_printf("Aff: %c\n", c);
	return (0);
}
