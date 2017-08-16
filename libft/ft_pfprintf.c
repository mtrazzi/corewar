/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 16:00:59 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/07/17 14:46:25 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf_aux_aux(t_var *x)
{
	if (x->f->type == 'C')
		ft_print_c(x);
	else if (x->f->type == 'S')
		ft_print_s(x);
	else if (x->pre[0] == '-' && ft_strchr(x->mid, '0'))
	{
		if (x->mid[0] == '0')
			ft_final_print(x->pre, x->mid, x->str, x->suf);
		else
			ft_final_print(" ", ft_insert_minus(x->mid), x->str, x->suf);
	}
	else if (x->f->type == 'c' && x->u->c == 0)
	{
		ft_putstr(x->mid);
		ft_putchar(0);
		ft_putstr(x->suf);
		return (0);
	}
	if (x->f->type == 'C' || x->f->type == 'S' || \
	(x->pre[0] == '-' && ft_strchr(x->mid, '0')))
		return (0);
	return (1);
}

void	ft_printf_aux(t_var *x)
{
	if (!ft_printf_aux_aux(x))
		return ;
	if (!ft_strncmp(x->pre, "+", 1) && !ft_strncmp(x->mid, " ", 1))
	{
		x->mid = ft_insert_plus(x->mid);
		change_pre(x, ft_strdup(" "));
	}
	if (x->f->opt[2] > '0')
		ft_final_print(x->pre, x->mid, x->str, x->suf);
	else if ((!ft_strncmp(x->pre, "+", 1) \
			|| !ft_strncmp(x->pre, " ", 1)) && x->f->type == 'd')
		ft_final_print(x->pre, x->mid, x->str, x->suf);
	else if (x->f->pre > 0 && ft_strchr(x->pre, '0'))
		ft_final_print(x->pre, x->mid, x->str, x->suf);
	else
		ft_final_print(x->mid, x->pre, x->str, x->suf);
}

size_t	ft_process(const char *format, va_list ap)
{
	size_t	result;
	t_var	*x;

	x = ft_init(format);
	ft_assign(x, ap);
	ft_conv_d(x);
	ft_insert(x);
	ft_printf_aux(x);
	if (x->f->type == 'C' || x->f->type == 'S')
		result = (x->f->type == 'C' ? ft_ret_c(x) : ft_ret_s(x));
	else
		result = ft_strlen(x->mid) + ft_strlen(x->pre) + \
		ft_strlen(x->str) + ft_strlen(x->suf);
	ft_free_all(x);
	return (result);
}

void	ft_update(size_t *ret, const char *restrict *format, int n)
{
	ft_putchar(*(*format));
	*format = *format + n;
	*ret = *ret + 1;
}

int		ft_printf(const char *restrict format, ...)
{
	va_list	ap;
	size_t	ret;

	ret = 0;
	va_start(ap, format);
	while (*format != '\0')
	{
		if (!ft_strncmp("%%", format, 2))
			ft_update(&ret, &format, 2);
		else if (*format == '%' && ft_next_conversion(format + 1))
		{
			ret += ft_process(format, ap);
			format = ft_strchr(format + 1, ft_next_conversion(format + 1)) + 1;
		}
		else
			ft_update(&ret, &format, 1);
	}
	va_end(ap);
	return (ret);
}
