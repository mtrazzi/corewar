/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/15 21:21:59 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/07/17 13:09:28 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_size_c_i(t_var *x, size_t i)
{
	int		n;
	size_t	res;

	n = ft_count_bits(x->u->ls[i]);
	if (n <= 7)
		res = 1;
	else if (n <= 11)
		res = 2;
	else if (n <= 16)
		res = 3;
	else
		res = 4;
	return (res);
}

size_t	ft_size_s(t_var *x)
{
	size_t	i;
	size_t	sum;
	wchar_t	*s;

	i = 0;
	sum = 0;
	s = x->u->ls;
	while (s[i])
	{
		sum += ft_size_c_i(x, i);
		i++;
	}
	return (sum);
}

void	ft_print_s_minus(t_var *x)
{
	size_t nb_bytes;
	size_t i;

	nb_bytes = ft_size_s(x);
	i = nb_bytes;
	ft_putstr_uni(x->u->ls);
	while (i < x->f->min)
	{
		ft_putchar(' ');
		i++;
	}
}

void	ft_print_s(t_var *x)
{
	size_t nb_bytes;
	size_t i;

	nb_bytes = ft_size_s(x);
	if (x->f->opt[0] > '0')
	{
		ft_print_s_minus(x);
		return ;
	}
	i = 0;
	while (i + nb_bytes < x->f->min)
	{
		ft_putchar(' ');
		i++;
	}
	ft_putstr_uni(x->u->ls);
}

size_t	ft_ret_s(t_var *x)
{
	if (x->f->min >= ft_size_s(x))
		return (x->f->min);
	else
		return (ft_size_s(x));
}
