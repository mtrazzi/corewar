/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cvt_inv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 16:54:36 by pkirsch           #+#    #+#             */
/*   Updated: 2017/05/23 19:50:19 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <limits.h>
#include <stdlib.h>

static void		pad(int n, int c, int put(int ch))
{
	while (n-- > 0)
		put(c);
}

static int		padding_left_justified(t_options *op, int put(int c))
{
	if ((op->flags['-']))
		pad(op->width - 1, ' ', put);
	return (1);
}

static void		uni_put(t_options *op, unsigned int c, unsigned int uni_lvl,
						int put(int c))
{
	if (uni_lvl == 1)
	{
		put(c);
		padding_left_justified(op, put);
	}
	else if (uni_lvl == 2)
	{
		put((c & 0xFF00) >> 8);
		padding_left_justified(op, put);
		put(c & 0xFF);
	}
	else if (uni_lvl == 3 || uni_lvl == 4)
	{
		(void)(uni_lvl == 4 ? (put((c & 0xFF000000) >> 24)
									| padding_left_justified(op, put)) : 1);
		put((c & 0xFF0000) >> 16);
		uni_lvl == 3 ? padding_left_justified(op, put) : 1;
		put((c & 0xFF00) >> 8);
		put(c & 0xFF);
	}
}

int				cvt_bad_ident(t_options *op, unsigned int c,
					unsigned int uni_lvl, int put(int c))
{
	if (op->width == INT_MIN)
		op->width = 0;
	if (op->width < 0)
	{
		op->flags['-'] = 1;
		op->width = -(op->width);
	}
	if (!(op->flags['-']))
		pad(op->width - 1, op->flags['0'] ? '0' : ' ', put);
	uni_put(op, c, uni_lvl, put);
	return (1);
}
