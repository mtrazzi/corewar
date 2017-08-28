/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_format.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 17:04:31 by pkirsch           #+#    #+#             */
/*   Updated: 2017/05/23 21:26:27 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "util.h"
#include "primary.h"
#include <limits.h>
#include <stdlib.h>
#include "ft_color.h"

static t_cvt_func g_cvt[256] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, cvt_percent, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, cvt_b, cvt_lc, cvt_d, 0, cvt_f, 0,
	0, 0, 0, 0, 0, 0, cvt_n, cvt_o,
	0, 0, 0, cvt_ls, 0, cvt_u, 0, 0,
	cvt_x, 0, 0, 0, 0, 0, 0, 0,
	0, 0, cvt_b, cvt_c, cvt_d, 0, cvt_f, 0,
	0, cvt_d, 0, 0, 0, 0, cvt_n, cvt_o,
	cvt_p, 0, 0, cvt_s, 0, cvt_u, 0, 0,
	cvt_x, 0, 0, 0, 0, 0, 0, 0
};

static int	get_code(t_options *op, const char *fmt, int put(int c))
{
	unsigned int bad_ident;
	unsigned int uni_lvl;
	unsigned int i;

	if (!(*fmt))
		return (0);
	uni_lvl = get_unitype(*fmt);
	if (uni_lvl == 1 && g_cvt[(int)*fmt])
	{
		op->code = *fmt;
		return (1);
	}
	else if (uni_lvl != 10000)
	{
		op->code = 0;
		bad_ident = 0;
		i = -1;
		while (++i < uni_lvl)
			bad_ident = bad_ident << 8 | (unsigned char)*(fmt + i);
		cvt_bad_ident(op, bad_ident, uni_lvl, put);
		return (uni_lvl);
	}
	else
		return (1);
}

static int	launch_convert(int *error, va_list *ap,
						t_options *options, int put(int c))
{
	if (g_cvt[options->code])
	{
		if (((*g_cvt[options->code])(options, ap, put)) == -1)
		{
			*error = 1;
			return (-1);
		}
	}
	return (1);
}

static int	clean_exit(t_options **op)
{
	free(*op);
	*op = NULL;
	return (-1);
}

int			get_format(int put(int c), const char *fmt, va_list ap, int *error)
{
	t_options *options;

	if ((options = init_options()) == NULL)
		return (-1);
	while (*fmt)
	{
		if ((*fmt != '%' || *++fmt == '%') && *fmt != '{')
			put((unsigned char)*fmt++);
		else if (*fmt == '{')
			do_color(&fmt, put);
		else if (*fmt)
		{
			get_optional_flags(&fmt, options->flags);
			get_optional_width_and_precision(&fmt, options, (va_list*)ap);
			get_optional_length_flags(&fmt, options->flags);
			fmt += get_code(options, fmt, put);
			if (launch_convert(error, (va_list*)ap, options, put) == -1)
				return (clean_exit(&options));
			reset_options(options);
		}
	}
	free(options);
	return (1);
}
