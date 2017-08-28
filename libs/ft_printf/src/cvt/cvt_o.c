/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cvt_o.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 14:44:28 by pkirsch           #+#    #+#             */
/*   Updated: 2017/05/19 17:05:56 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <limits.h>
#include <stdlib.h>

static void		val_retriever(int code, unsigned long long *val, va_list *app,
						t_options *op)
{
	if (code == 'O')
	{
		op->code = 'o';
		*val = va_arg(*app, unsigned long);
	}
	else if (op->flags['h'] == 1)
		*val = (unsigned short)va_arg(*app, int);
	else if (op->flags['h'] == 2)
		*val = (unsigned char)va_arg(*app, int);
	else if (op->flags['l'] == 1)
		*val = va_arg(*app, unsigned long);
	else if (op->flags['l'] == 2)
		*val = va_arg(*app, unsigned long long);
	else if (op->flags['j'] == 1)
		*val = va_arg(*app, uintmax_t);
	else if (op->flags['z'] == 1)
		*val = va_arg(*app, size_t);
	else
		*val = va_arg(*app, unsigned int);
}

int				cvt_o(t_options *op, va_list *app, int put(int c))
{
	unsigned long long	m;
	unsigned long long	tmp;
	char				buf[43];
	char				*p;

	p = buf + sizeof(buf);
	val_retriever(op->code, &m, app, op);
	tmp = m;
	if (m == 0)
	{
		op->zero = 1;
		*--p = '0';
	}
	while (m != 0)
	{
		*--p = (m & 0x7) + '0';
		m >>= 3;
	}
	if (tmp && op->flags['#'])
		*--p = '0';
	ft_puto(p, (buf + sizeof(buf)) - p, put, op);
	return (1);
}
