/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 14:28:10 by pkirsch           #+#    #+#             */
/*   Updated: 2017/05/23 20:05:00 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "util.h"
#include <limits.h>

char		*g_sprintf_buf = 0;
long long	g_sprintf_index = 0;

long long	get_sprintf_index(void)
{
	return (g_sprintf_index);
}

static int	outs(int c)
{
	if (g_sprintf_index == INT_MAX - 1)
		return (-1);
	g_sprintf_buf[g_sprintf_index++] = c;
	return (1);
}

int			ft_sprintf(char *str, const char *fmt, ...)
{
	long long	tmp;
	int			error;
	va_list		ap;

	g_sprintf_buf = str;
	error = 0;
	va_start(ap, fmt);
	if (get_format(outs, fmt, ap, &error) == -1)
	{
		ft_strclr(str);
		g_sprintf_index = 0;
		g_sprintf_buf = NULL;
		va_end(ap);
		return (-1);
	}
	g_sprintf_buf[g_sprintf_index] = '\0';
	va_end(ap);
	tmp = g_sprintf_index;
	g_sprintf_index = 0;
	g_sprintf_buf = NULL;
	return (tmp);
}

int			ft_vsprintf(char *str, const char *fmt, va_list ap)
{
	long long	tmp;
	int			error;

	g_sprintf_buf = str;
	error = 0;
	if (get_format(outs, fmt, ap, &error) == -1)
	{
		ft_strclr(str);
		g_sprintf_index = 0;
		g_sprintf_buf = NULL;
		return (-1);
	}
	g_sprintf_buf[g_sprintf_index] = '\0';
	tmp = g_sprintf_index;
	g_sprintf_index = 0;
	g_sprintf_buf = NULL;
	return (tmp);
}
