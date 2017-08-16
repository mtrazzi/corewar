/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 16:00:45 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/07/17 13:09:13 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_var	*ft_init(const char *format)
{
	t_var *x;
	t_val *v;

	if (!(x = (t_var *)malloc(sizeof(t_var))))
		exit(EXIT_FAILURE);
	x = ft_parse(format, x);
	if (!(v = (t_val *)malloc(sizeof(t_val))))
		exit(EXIT_FAILURE);
	x->u = v;
	x->mid = ft_strdup("");
	x->pre = ft_strdup("");
	x->str = ft_strdup("");
	x->suf = ft_strdup("");
	return (x);
}
