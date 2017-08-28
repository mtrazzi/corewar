/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cvt_lc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 14:39:23 by pkirsch           #+#    #+#             */
/*   Updated: 2017/05/22 22:57:20 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_put.h"
#include <limits.h>

static int	ft_bitscount_local(unsigned int n)
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

static int	get_uni_local(int c)
{
	int		bc;

	bc = ft_bitscount_local(c);
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

int			cvt_lc(t_options *op, va_list *app, int put(int c))
{
	int c;
	int len;

	c = va_arg(*app, int);
	if (MB_CUR_MAX == 4 && ((c >= 0xD800 && c <= 0xDFFF) || c > 0x10FFFF))
		return (-1);
	len = (MB_CUR_MAX == 1) ? 1 : get_uni_local(c);
	if (op->width == INT_MIN)
		op->width = 0;
	if (op->width < 0)
	{
		op->flags['-'] = 1;
		op->width = -(op->width);
	}
	if (!(op->flags['-']))
		pad(op->width - len, op->flags['0'] ? '0' : ' ', put);
	if (uni(c, put) == -1)
		return (-1);
	if ((op->flags['-']))
		pad(op->width - len, ' ', put);
	return (1);
}
