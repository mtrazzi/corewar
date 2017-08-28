/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 15:10:09 by pkirsch           #+#    #+#             */
/*   Updated: 2017/05/19 20:02:23 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_put.h"

static int	get_unitype2(char c)
{
	if ((c & 0xF8) == 0xF0)
	{
		return (4);
	}
	else if ((c & 0xF0) == 0xE0)
	{
		return (3);
	}
	else if ((c & 0xE0) == 0xC0)
	{
		return (2);
	}
	else if ((c & 0x80) == 0)
	{
		return (1);
	}
	return (10000);
}

static int	new_length(const char *str)
{
	int i;
	int result;
	int length;

	i = 0;
	length = 0;
	while (str[i])
	{
		result = get_unitype2(str[i]);
		i += result;
		length += result;
	}
	return (length);
}

static void	emit_str(int len, const char *str, int put(int c))
{
	int i;

	i = 0;
	while (i < len)
	{
		put((unsigned char)*str++);
		i++;
	}
}

void		ft_puts(const char *str, int len, int put(int c), t_options *op)
{
	int new_l;

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
	new_l = new_length(str);
	if (op->precision >= 0 && op->precision < len)
	{
		new_l = op->precision;
		len = op->precision;
	}
	if (!(op->flags['-']))
		pad(op->width - new_l, op->flags['0'] ? '0' : ' ', put);
	emit_str(len, str, put);
	if ((op->flags['-']))
		pad(op->width - new_l, ' ', put);
}
