/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 19:18:51 by pkirsch           #+#    #+#             */
/*   Updated: 2017/05/23 19:52:37 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_put.h"

static void	normalize_width_and_flags(const char **str, int *len, t_options *op,
									int *sign)
{
	if (op->width == INT_MIN)
		op->width = 0;
	if (op->width < 0)
	{
		op->flags['-'] = 1;
		op->width = -(op->width);
	}
	if (*len > 0 && (**str == '-' || **str == '+'))
	{
		*sign = **str;
		(*str)++;
		(*len)--;
	}
	else if (op->flags['+'])
		*sign = '+';
	else if (op->flags[' '])
		*sign = ' ';
	else
		*sign = 0;
}

static void	emit_str_justified_in_width_prep(t_options *op, int sign, int n,
									int put(int c))
{
	if (op->flags['-'])
	{
		if (sign)
			put(sign);
	}
	else if (op->flags['0'])
	{
		if (sign)
			put(sign);
		pad(op->width - n, '0', put);
	}
	else
	{
		pad(op->width - n, ' ', put);
		if (sign)
			put(sign);
	}
}

static void	emit_str(const char *str, int len, int put(int c))
{
	int i;

	i = 0;
	while (i++ < len)
		put((unsigned char)*str++);
}

void		ft_putf(const char *str, int len, int put(int c), t_options *op)
{
	int sign;
	int n;

	normalize_width_and_flags(&str, &len, op, &sign);
	if (op->precision < 0)
	{
		if (op->precision == INT_MIN)
			op->no_precision = 1;
		op->precision = 1;
	}
	if (len < op->precision)
		n = op->precision;
	else if (op->precision == 0 && len == 1 && str[0] == '0')
		n = 0;
	else
		n = len;
	if (sign)
		n++;
	emit_str_justified_in_width_prep(op, sign, n, put);
	pad(op->precision - len, '0', put);
	emit_str(str, len, put);
	if (op->flags['-'])
		pad(op->width - n, ' ', put);
}
