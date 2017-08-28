/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cvt_p.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 13:39:31 by pkirsch           #+#    #+#             */
/*   Updated: 2017/05/19 17:05:59 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <limits.h>

int		cvt_p(t_options *op, va_list *app, int put(int c))
{
	unsigned long	m;
	char			buf[44];
	char			*p;

	p = buf + sizeof(buf);
	m = (unsigned long)va_arg(*app, void*);
	if (m == 0)
	{
		op->zero = 1;
		*--p = "0123456789abcdef"[m & 0xf];
	}
	while (m != 0)
	{
		*--p = "0123456789abcdef"[m & 0xf];
		m >>= 4;
	}
	ft_putp(p, (buf + sizeof(buf)) - p, put, op);
	return (1);
}
