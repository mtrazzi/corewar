/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 19:11:29 by pkirsch           #+#    #+#             */
/*   Updated: 2017/05/23 20:05:07 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "util.h"

static int	next_arg_or_scan_digits(const char **fmt, va_list *ap)
{
	int n;
	int d;

	if (**fmt == '*')
	{
		n = va_arg(*ap, int);
		(*fmt)++;
	}
	else
	{
		n = 0;
		while (ft_isdigit(**fmt))
		{
			d = **fmt - '0';
			n = 10 * n + d;
			(*fmt)++;
		}
	}
	return (n);
}

void		get_optional_length_flags(const char **fmt, unsigned char *flags)
{
	unsigned char	ch;
	char			*fmt_flags;

	fmt_flags = "hljzL";
	ch = **fmt;
	while (ch && ft_strchr(fmt_flags, ch))
	{
		flags[ch]++;
		(*fmt)++;
		ch = **fmt;
	}
}

void		get_optional_flags(const char **fmt, unsigned char *flags)
{
	char			*fmt_flags;
	unsigned char	ch;

	fmt_flags = "#-+ 0";
	ch = **fmt;
	while (ch && ft_strchr(fmt_flags, ch))
	{
		flags[ch]++;
		(*fmt)++;
		ch = **fmt;
	}
}

void		get_optional_width_and_precision(const char **fmt,
						t_options *options, va_list *ap)
{
	while (**fmt == '*' || ft_isdigit(**fmt))
		options->width = next_arg_or_scan_digits(fmt, ap);
	if (**fmt == '.')
	{
		options->flags['.'] = 1;
		(*fmt)++;
		if ((**fmt == '*' || ft_isdigit(**fmt)))
			options->precision = next_arg_or_scan_digits(fmt, ap);
	}
}
