/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cvt_d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 14:41:21 by pkirsch           #+#    #+#             */
/*   Updated: 2017/05/23 19:00:40 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <limits.h>
#include <stdlib.h>

static void		val_retriever(int code, long long *val, va_list *app,
						t_options *op)
{
	if (code == 'D' || code == 'I')
	{
		op->code = 'd';
		*val = va_arg(*app, long);
	}
	else if (op->flags['j'] == 1)
		*val = va_arg(*app, intmax_t);
	else if (op->flags['z'] == 1)
		*val = va_arg(*app, long);
	else if (op->flags['l'] == 2)
		*val = va_arg(*app, long long);
	else if (op->flags['l'] == 1)
		*val = va_arg(*app, long);
	else if (op->flags['h'] == 1)
		*val = (short)va_arg(*app, int);
	else if (op->flags['h'] == 2)
		*val = (signed char)va_arg(*app, int);
	else
		*val = va_arg(*app, int);
}

static int		max(t_options *op, long long val, int put(int c))
{
	if ((val << 1 == 0 && val >> 63) ||
			(val << 1 == 0 && (val >> 63) >> 63 == 2))
	{
		if (sizeof(long long) == 8)
			ft_putd("-9223372036854775808", 20, put, op);
		else
			ft_putd("-170141183460469231731687303715884105728", 40, put, op);
		return (1);
	}
	return (0);
}

int				cvt_d(t_options *op, va_list *app, int put(int c))
{
	long long	val;
	long long	m;
	char		buf[43];
	char		*p;

	p = buf + sizeof(buf);
	val_retriever(op->code, &val, app, op);
	if (max(op, val, put))
		return (1);
	m = (val < 0 ? -val : val);
	if (m == 0)
	{
		op->zero = 1;
		*--p = '0';
	}
	while (m > 0)
	{
		*--p = m % 10 + '0';
		m /= 10;
	}
	if (val < 0)
		*--p = '-';
	ft_putd(p, (buf + sizeof(buf)) - p, put, op);
	return (1);
}
