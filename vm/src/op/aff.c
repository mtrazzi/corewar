/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 14:49:21 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/09/10 14:49:22 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	aff(t_env *e, t_prc *prc)
{
	unsigned char c;

	c = (unsigned char)get_value(e, REG_CODE, prc, prc->pc + 2);
	//printf("%c", c); //to change when option aff will be ready
	return (0);
}
