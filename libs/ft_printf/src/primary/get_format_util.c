/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_format_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 18:50:37 by pkirsch           #+#    #+#             */
/*   Updated: 2017/05/23 20:05:14 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cvt.h"
#include "util.h"
#include <limits.h>
#include <stdlib.h>

t_options	*init_options(void)
{
	t_options *options;

	if (!(options = (t_options *)malloc(sizeof(t_options))))
		return (NULL);
	ft_memset(options->flags, '\0', sizeof(options->flags));
	options->width = INT_MIN;
	options->precision = INT_MIN;
	options->no_precision = 0;
	options->code = 0;
	options->zero = 0;
	return (options);
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
