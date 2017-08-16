/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 16:00:42 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/07/17 13:09:11 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_free_all(t_var *x)
{
	free(x->f->opt);
	free(x->f);
	free(x->u);
	free(x->mid);
	free(x->pre);
	free(x->str);
	free(x->suf);
	free(x);
}

void	ft_final_print(char *s1, char *s2, char *s3, char *s4)
{
	ft_putstr(s1);
	ft_putstr(s2);
	ft_putstr(s3);
	ft_putstr(s4);
}
