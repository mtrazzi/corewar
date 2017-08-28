/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cvt_x.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 12:52:32 by pkirsch           #+#    #+#             */
/*   Updated: 2017/05/19 17:06:16 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <limits.h>
#include <stdlib.h>

static void		val_retriever(unsigned long long *val, va_list *app,
						unsigned char flags[])
{
	if (flags['h'] == 1)
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

int				cvt_x(t_options *op, va_list *app, int put(int c))
{
	unsigned long long	m;
	unsigned long long	tmp;
	char				buf[43];
	char				*p;
	char				*base;

	p = buf + sizeof(buf);
	val_retriever(&m, app, op->flags);
	base = (op->code == 'x') ? "0123456789abcdef" : "0123456789ABCDEF";
	tmp = m;
	if (m == 0)
	{
		op->zero = 1;
		*--p = base[0];
	}
	while (m != 0)
	{
		*--p = base[m & 0xf];
		m >>= 4;
	}
	ft_putx(p, (buf + sizeof(buf)) - p, put, op);
	return (1);
}
