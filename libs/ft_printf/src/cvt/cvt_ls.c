/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cvt_ls.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 13:29:08 by pkirsch           #+#    #+#             */
/*   Updated: 2017/05/23 20:05:26 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "util.h"
#include <stdarg.h>
#include <limits.h>
#include <stdlib.h>

static int	ft_strlen_wchar(wchar_t *str)
{
	int count;

	count = 0;
	while (*str++)
		count++;
	return (count);
}

int			cvt_ls(t_options *op, va_list *app, int put(int c))
{
	wchar_t *str;

	str = va_arg(*app, wchar_t *);
	if (str == NULL)
		str = L"(null)";
	if (ft_putls(str, ft_strlen_wchar(str), put, op) == -1)
		return (-1);
	return (1);
}
