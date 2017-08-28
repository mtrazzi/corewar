/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 17:03:50 by pkirsch           #+#    #+#             */
/*   Updated: 2017/05/23 20:41:01 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "util.h"
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>

long long	g_printf_ret = 0;
int			g_pr_witness = 0;
int			g_print_fd = 1;

static int	out2(int c)
{
	g_printf_ret += write(g_print_fd, &c, 1);
	return (g_printf_ret);
}

long long	get_ret_value(void)
{
	if (g_pr_witness == 0)
		return (get_sprintf_index());
	return (g_printf_ret);
}

int			ft_printf(const char *fmt, ...)
{
	int		tmp;
	int		error;
	va_list	ap;

	error = 0;
	g_pr_witness = 1;
	va_start(ap, fmt);
	if (get_format(out2, fmt, ap, &error) == -1)
	{
		g_printf_ret = 0;
		g_pr_witness = 0;
		va_end(ap);
		return (-1);
	}
	va_end(ap);
	tmp = g_printf_ret;
	g_printf_ret = 0;
	g_pr_witness = 0;
	return (tmp);
}

int			ft_fprintf(int fd, const char *fmt, ...)
{
	int		tmp;
	int		error;
	va_list	ap;

	error = 0;
	g_pr_witness = 1;
	g_print_fd = fd;
	va_start(ap, fmt);
	if (get_format(out2, fmt, ap, &error) == -1)
	{
		g_printf_ret = 0;
		g_pr_witness = 0;
		g_print_fd = 1;
		va_end(ap);
		return (-1);
	}
	va_end(ap);
	tmp = g_printf_ret;
	g_print_fd = 1;
	g_printf_ret = 0;
	g_pr_witness = 0;
	return (tmp);
}
