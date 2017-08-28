/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cvt_f.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 17:02:28 by pkirsch           #+#    #+#             */
/*   Updated: 2017/05/23 20:05:20 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "util.h"
#include <limits.h>
#include <float.h>

static void			val_retriever(int code, long double *val, va_list *app,
								unsigned char flags[])
{
	if (flags['L'])
		*val = va_arg(*app, double);
	else if (code == 'f' || code == 'F')
		*val = va_arg(*app, double);
}

static long long	rounding(long double decpart, long long *intpart,
								t_options *op)
{
	int			len;
	long long	dec;
	long long	tmp;

	dec = (long long)(decpart + 0.5);
	len = 0;
	tmp = dec;
	while (tmp)
	{
		len++;
		tmp /= 10;
	}
	if (len > op->precision)
	{
		*intpart += 1;
		dec = 0;
	}
	return (dec);
}

static void			decpart_to_buff(long double decpart, long long *intpart,
								char **p, t_options *op)
{
	int			tmp;
	long long	dec;

	dec = rounding(decpart, intpart, op);
	tmp = op->precision;
	while (!dec && tmp--)
	{
		(*p)--;
		**p = '0';
	}
	while (dec > 0)
	{
		(*p)--;
		**p = dec % (long long)10 + '0';
		dec /= (long long)10;
	}
	if (op->precision || op->flags['#'])
	{
		(*p)--;
		**p = '.';
	}
}

static void			intpart_sign_to_buff(long double val, long long intpart,
								char **p)
{
	if (intpart == 0)
	{
		(*p)--;
		**p = '0';
	}
	while (intpart > 0)
	{
		(*p)--;
		**p = intpart % (long long)10 + '0';
		intpart /= (long long)10;
	}
	if (val < 0)
	{
		(*p)--;
		**p = '-';
	}
}

int					cvt_f(t_options *op, va_list *app, int put(int c))
{
	char		buf[DBL_MAX_10_EXP + 1 + 1 + 18 + 1];
	char		*p;
	long double	val;
	long long	intpart;
	long double	decpart;

	p = buf + sizeof(buf);
	val_retriever(op->code, &val, app, op->flags);
	intpart = (long long)((val < 0) ? -val : val);
	decpart = ((val < 0) ? -val : val) - intpart;
	if (op->precision < 0 && op->flags['.'])
		op->precision = 0;
	else if (op->precision < 0)
		op->precision = 6;
	if (op->precision > 18)
		op->precision = 18;
	decpart *= (iterative_power_long_double(10, op->precision)
		* ((op->precision) ? 1.0 : 0.0));
	decpart_to_buff(decpart, &intpart, &p, op);
	intpart_sign_to_buff(val, intpart, &p);
	ft_putf(p, (buf + sizeof(buf)) - p, put, op);
	return (1);
}
