/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cvt_percent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 17:45:18 by pkirsch           #+#    #+#             */
/*   Updated: 2017/05/23 19:49:56 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <limits.h>

static void		pad(int n, int c, int put(int ch))
{
	while (n-- > 0)
		put(c);
}

int				cvt_percent(t_options *op, va_list *app, int put(int c))
{
	(void)app;
	if (op->width == INT_MIN)
		op->width = 0;
	if (op->width < 0)
	{
		op->flags['-'] = 1;
		op->width = -(op->width);
	}
	if (!(op->flags['-']))
		pad(op->width - 1, (op->flags['0']) ? '0' : ' ', put);
	put('%');
	if ((op->flags['-']))
		pad(op->width - 1, ' ', put);
	return (1);
}
