/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 16:00:36 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/07/16 19:00:05 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	change_pre(t_var *x, char *str)
{
	if (!str)
		exit(EXIT_FAILURE);
	free(x->pre);
	x->pre = str;
}

void	change_str(t_var *x, char *str)
{
	if (!str && (x->f->type == 's' && x->u->s == NULL))
		change_str(x, "(null)");
	if (!str)
		exit(EXIT_FAILURE);
	free(x->str);
	x->str = str;
}

void	change_mid(t_var *x, char *str)
{
	if (!str)
		exit(EXIT_FAILURE);
	free(x->mid);
	x->mid = str;
}

void	change_suf(t_var *x, char *str)
{
	if (!str)
		exit(EXIT_FAILURE);
	free(x->suf);
	x->suf = str;
}
