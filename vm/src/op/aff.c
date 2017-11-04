/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 14:49:21 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/11/04 14:59:48 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	aff(t_env *e, t_prc *prc)
{
	unsigned char c;

	c = (unsigned char)get_value(e, REG_CODE, prc, prc->pc + 2);
	if (e->par.opts & OPT_A)
		printf("Aff: %c\n", c); //to change when option aff will be ready
	return (0);
}
