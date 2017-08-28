/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 19:54:01 by pkirsch           #+#    #+#             */
/*   Updated: 2017/05/23 20:04:57 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "util.h"
#include "ft_put.h"
#include <stdarg.h>
#include <limits.h>
#include <stdlib.h>

static int	new_length(const wchar_t *str)
{
	int i;
	int result;
	int length;

	i = 0;
	length = 0;
	while (str[i])
	{
		result = get_uni(str[i]);
		i++;
		length += result;
	}
	return (length);
}

static int	new_length_with_precision(const wchar_t *str, int precision)
{
	int i;
	int length;
	int ret;

	i = 0;
	length = 0;
	while (str[i])
	{
		ret = get_uni(str[i]);
		if (length + ret <= precision)
			length += ret;
		else
			break ;
		i++;
	}
	return (length);
}

static int	emit_str(const wchar_t *str, int len, int put(int c), t_options *op)
{
	int ret;
	int i;

	i = 0;
	while (((i + get_uni(*str)) <= len) && op->precision >= 0)
	{
		ret = uni(*str++, put);
		if (ret == -1)
			return (-1);
		else
			i += ret;
	}
	while (i < len && op->precision < 0)
	{
		ret = uni(*str++, put);
		if (ret == -1)
			return (-1);
		i++;
	}
	return (1);
}

static void	normalize_witdh_prec_flags(t_options *op)
{
	if (op->width == INT_MIN)
		op->width = 0;
	if (op->width < 0)
	{
		op->flags['-'] = 1;
		op->width = -(op->width);
	}
	if (op->precision >= 0)
		op->flags['0'] = 0;
	if (op->precision == INT_MIN && op->flags['.'])
		op->precision = 0;
}

int			ft_putls(const wchar_t *str, int len, int put(int c), t_options *op)
{
	int new_l;
	int j;

	j = 0;
	while (j < len)
	{
		if (MB_CUR_MAX == 4 && ((str[j] >= 0xD800 && str[j] <= 0xDFFF)
			|| str[j] > 0x10FFFF))
			return (-1);
		j++;
	}
	normalize_witdh_prec_flags(op);
	new_l = (MB_CUR_MAX == 1) ? len : new_length(str);
	if (op->precision >= 0 && op->precision < new_l)
	{
		new_l = new_length_with_precision(str, op->precision);
		len = op->precision;
	}
	if (!(op->flags['-']))
		pad(op->width - new_l, op->flags['0'] ? '0' : ' ', put);
	if (emit_str(str, len, put, op) == -1)
		return (-1);
	if ((op->flags['-']))
		pad(op->width - new_l, ' ', put);
	return (1);
}
