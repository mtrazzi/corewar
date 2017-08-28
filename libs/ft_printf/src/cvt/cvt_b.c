/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cvt_b.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 14:35:59 by pkirsch           #+#    #+#             */
/*   Updated: 2017/05/23 20:05:23 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "util.h"
#include <stdarg.h>
#include <limits.h>
#include <stdlib.h>

static void			val_retriever(int code, unsigned long long *val,
							va_list *app, unsigned char flags[])
{
	if (code == 'B')
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

static long long	i_mask(int code, unsigned char flags[])
{
	if (code == 'B')
		return (0x8000000000000000);
	else if (flags['h'] == 1)
		return (0x8000);
	else if (flags['h'] == 2)
		return (0x80);
	else if (flags['l'] == 1)
		return (0x8000000000000000);
	else if (flags['l'] == 2)
		return (0x8000000000000000);
	else if (flags['j'] == 1)
		return (0x8000000000000000);
	else if (flags['z'] == 1)
		return (0x8000000000000000);
	else
		return (0x80000000);
}

int					cvt_b(t_options *op, va_list *app, int put(int c))
{
	unsigned long long	m;
	char				buf[66];
	unsigned long long	i;
	int					j;

	j = 0;
	val_retriever(op->code, &m, app, op->flags);
	i = i_mask(op->code, op->flags);
	if (op->flags['#'])
	{
		buf[j++] = '0';
		buf[j++] = 'b';
	}
	while (i > 0)
	{
		buf[j++] = ((m & i) ? '1' : '0');
		i >>= 1;
	}
	ft_putd(buf, j, put, op);
	return (1);
}
