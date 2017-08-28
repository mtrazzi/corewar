/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cvt_s.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 14:47:55 by pkirsch           #+#    #+#             */
/*   Updated: 2017/05/23 20:05:29 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "util.h"
#include <stdarg.h>

int	cvt_s(t_options *op, va_list *app, int put(int c))
{
	char *str;

	if (op->flags['l'])
		return (cvt_ls(op, (va_list *)app, put));
	str = va_arg(*app, char *);
	if (str == NULL)
		str = "(null)";
	ft_puts(str, ft_strlen(str), put, op);
	return (1);
}
