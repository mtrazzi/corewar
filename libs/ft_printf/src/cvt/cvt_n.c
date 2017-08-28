/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cvt_n.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 23:00:01 by pkirsch           #+#    #+#             */
/*   Updated: 2017/05/23 19:52:02 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <limits.h>
#include <stdlib.h>

int				cvt_n(t_options *op, va_list *app, int put(int c))
{
	(void)put;
	if (op->code == 'N')
		*(va_arg(*app, long *)) = get_ret_value();
	else if (op->flags['h'] == 1)
		*(va_arg(*app, short *)) = get_ret_value();
	else if (op->flags['h'] == 2)
		*(va_arg(*app, signed char *)) = get_ret_value();
	else if (op->flags['l'] == 1)
		*(va_arg(*app, long *)) = get_ret_value();
	else if (op->flags['l'] == 2)
		*(va_arg(*app, long long *)) = get_ret_value();
	else if (op->flags['j'] == 1)
		*(va_arg(*app, intmax_t *)) = get_ret_value();
	else if (op->flags['z'] == 1)
		*(va_arg(*app, long long *)) = get_ret_value();
	else
		*(va_arg(*app, int *)) = get_ret_value();
	return (1);
}
