/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 16:00:47 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/07/17 13:23:12 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_var	*ft_insert_pre(t_var *x)
{
	char c;

	if (x->f->opt[4] != '0' && !ft_is_null_u(x))
	{
		c = (x->f->opt)[4];
		if (c == 'x')
			change_pre(x, ft_strdup("0x"));
		else if (c == 'X')
			change_pre(x, ft_strdup("0X"));
		else if (c == 'o' || c == 'O')
			change_pre(x, ft_strdup("0"));
		return (x);
	}
	if (x->f->opt[1] > '0')
		change_pre(x, ft_strdup("+"));
	if (x->f->opt[3] > '0' && !(x->f->type == '%'))
		change_pre(x, ft_strdup(" "));
	return (x);
}

t_var	*ft_insert_start(t_var *x)
{
	size_t	n;
	size_t	pre_len;
	size_t	str_len;
	size_t	m;

	n = 0;
	m = 0;
	pre_len = (x->f->type == 'o' ? ft_strlen(x->pre) : 0);
	str_len = ft_strlen(x->str);
	while (n + str_len + pre_len < x->f->pre)
		n++;
	if (x->f->type == 's')
		n = 0;
	change_mid(x, ft_memset(ft_strnew(n), '0', n));
	while (m + n + str_len + ft_strlen(x->pre) < x->f->min)
		m++;
	change_suf(x, ft_memset(ft_strnew(m), ' ', m));
	return (x);
}

t_var	*ft_insert_mid_suf_aux(t_var *x)
{
	if ((!ft_strncmp(x->pre, "+", 1) || !ft_strncmp(x->pre, " ", 1)) \
	&& ft_atoi(x->str) < 0)
		change_pre(x, ft_strdup(""));
	if ((x->f->pre != 0 || x->f->opt[2] > '0') && ft_atoi(x->str) < 0 \
	&& (ft_strchr("di", x->f->type)))
	{
		change_str(x, ft_strdup(x->str + 1));
		change_pre(x, ft_strdup("-"));
	}
	if (x->f->pre != 0 && x->f->opt[2] > '0')
		x->f->opt[2] = '0';
	return (x);
}

t_var	*ft_insert_mid_suf(t_var *x)
{
	size_t	n;
	size_t	m;
	char	*str1;
	char	*str2;

	if (x->f->opt[0] > '0')
		return (ft_insert_start(x));
	x = ft_insert_mid_suf_aux(x);
	n = 0;
	m = 0;
	while (n + (x->f->type == 'o' ? ft_strlen(x->pre) : 0) + \
	ft_strlen(x->str) - (x->str[0] == '-') < x->f->pre)
		n++;
	if (x->f->type == 's')
		n = 0;
	while (m + n + ft_strlen(x->str) + ft_strlen(x->pre) < x->f->min)
		m++;
	if (!(str1 = ft_memset(ft_strnew(m), (x->f->opt[2] > '0' ? '0' : ' '), m)))
		exit(EXIT_FAILURE);
	if (!(str2 = ft_memset(ft_strnew(n), '0', n)))
		exit(EXIT_FAILURE);
	change_mid(x, ft_strjoin(str1, str2));
	free(str1);
	free(str2);
	return (x);
}

t_var	*ft_insert(t_var *x)
{
	char *str;

	if (x->f->type == 's' && !(x->str))
		return (x);
	if (x->f->type == 'c' && (x->u->c == 0))
	{
		change_str(x, ft_strdup(" "));
		x->f->type = 'd';
		x->f->len = 0;
		x->u->d = 1;
		x->f->pre = 0;
		ft_insert_str(x);
		ft_insert_mid_suf(x);
		x->f->type = 'c';
		x->u->c = 0;
		return (x);
	}
	if (x->f->type == 'c')
	{
		str = ft_strnew(1);
		str[0] = x->u->c;
		x->f->type = 's';
		x->u->s = str;
	}
	return (ft_insert_mid_suf(ft_insert_str(ft_insert_pre(x))));
}
