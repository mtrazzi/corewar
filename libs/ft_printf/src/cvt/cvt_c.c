/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cvt_c.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 13:39:51 by pkirsch           #+#    #+#             */
/*   Updated: 2017/05/19 17:05:08 by pkirsch          ###   ########.fr       */
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

int				cvt_c(t_options *op, va_list *app, int put(int c))
{
	unsigned char val;

	if (op->flags['l'])
		return (cvt_lc(op, (va_list *)app, put));
	if (op->width == INT_MIN)
		op->width = 0;
	if (op->width < 0)
	{
		op->flags['-'] = 1;
		op->width = -(op->width);
	}
	if (!(op->flags['-']))
		pad(op->width - 1, op->flags['0'] ? '0' : ' ', put);
	val = (unsigned char)va_arg(*app, int);
	put(val);
	if ((op->flags['-']))
		pad(op->width - 1, ' ', put);
	if (val >= 128 && MB_CUR_MAX == 1)
		return (-1);
	return (1);
}
