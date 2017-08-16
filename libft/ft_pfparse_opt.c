/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_opt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 16:00:55 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/07/17 13:09:24 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		is_opt(char c)
{
	return (c == '-' || c == '+' || c == '0' || c == ' ' || c == '#');
}

char	*ft_parse_opt_aux(const char *s)
{
	char *res;

	res = ft_strdup("00000");
	while (is_opt(*(++s)))
	{
		if (*s == '-')
			res[0] = '1';
		if (*s == '+')
			res[1] = '1';
		if (*s == '0')
			res[2] = '1';
		if (*s == ' ')
			res[3] = '1';
		if (*s == '#')
			res[4] = '1';
	}
	return (res);
}

t_var	*ft_parse_opt(const char *s, t_var *x)
{
	char	*res;
	t_for	*f;
	char	c;

	f = (t_for *)malloc(sizeof(t_for));
	res = ft_parse_opt_aux(s);
	if (res[0] > '0' && res[2] > '0')
		res[2] = '0';
	if (res[1] > '0' && res[3] > '0')
		res[3] = '0';
	c = ft_next_conversion(s + 1);
	if (res[4] > '0')
		res[4] = c;
	f->opt = res;
	x->f = f;
	return (x);
}
