/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cvt_u.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 14:42:37 by pkirsch           #+#    #+#             */
/*   Updated: 2017/05/19 17:06:11 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <limits.h>
#include <stdlib.h>

static void		val_retriever(int code, unsigned long long *val, va_list *app,
						unsigned char flags[])
{
	if (code == 'U')
		*val = va_arg(*app, unsigned long);
	else if (flags['h'] == 1)
		*val = (unsigned short)va_arg(*app, int);
	else if (flags['h'] == 2)
		*val = (unsigned char)va_arg(*app, int);
	else if (flags['l'] == 1)
		*val = va_arg(*app, unsigned long);
	else if (flags['l'] == 2)
		*val = va_arg(*app, unsigned long long);
	else if (flags['j'] == 1)
		*val = va_arg(*app, uintmax_t);
	else if (flags['z'] == 1)
		*val = va_arg(*app, size_t);
	else
		*val = va_arg(*app, unsigned int);
}

int				cvt_u(t_options *op, va_list *app, int put(int c))
{
	unsigned long long	m;
	char				buf[43];
	char				*p;

	p = buf + sizeof(buf);
	val_retriever(op->code, &m, app, op->flags);
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
	ft_putu(p, (buf + sizeof(buf)) - p, put, op);
	return (1);
}
