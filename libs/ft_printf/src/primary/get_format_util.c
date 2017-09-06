/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_format_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 18:50:37 by pkirsch           #+#    #+#             */
/*   Updated: 2017/09/06 17:27:53 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cvt.h"
#include "util.h"
#include <limits.h>
#include <stdlib.h>

void		init_options(t_options *options)
{
	ft_memset(options->flags, '\0', sizeof(options->flags));
	options->width = INT_MIN;
	options->precision = INT_MIN;
	options->no_precision = 0;
	options->code = 0;
	options->zero = 0;
}

void		reset_options(t_options *options)
{
	ft_memset(options->flags, '\0', sizeof(options->flags));
	options->width = INT_MIN;
	options->precision = INT_MIN;
	options->no_precision = 0;
	options->code = 0;
	options->zero = 0;
}

int			get_unitype(char c)
{
	if ((c & 0xF8) == 0xF0)
	{
		return (4);
	}
	else if ((c & 0xF0) == 0xE0)
	{
		return (3);
	}
	else if ((c & 0xE0) == 0xC0)
	{
		return (2);
	}
	else if ((c & 0x80) == 0)
	{
		return (1);
	}
	return (10000);
}
