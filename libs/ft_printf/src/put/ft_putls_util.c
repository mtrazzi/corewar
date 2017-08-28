/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putls_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 19:54:23 by pkirsch           #+#    #+#             */
/*   Updated: 2017/05/19 20:04:57 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_put.h"

static int	ft_bitscount(unsigned int n)
{
	int				count;
	unsigned int	i;

	if (!n)
		return (0);
	i = 0x80000000;
	while (!(n & i))
		i >>= 1;
	count = 0;
	while (i > 0)
	{
		count++;
		i >>= 1;
	}
	return (count);
}

int			get_uni(wchar_t c)
{
	int		bc;

	bc = ft_bitscount(c);
	if (bc <= 21)
	{
		if (bc <= 7)
			return (1);
		else if (bc <= 11)
			return (2);
		else if (bc <= 16)
			return (3);
		else if (bc <= 21)
			return (4);
	}
	return (-1);
}
