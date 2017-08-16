/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_uni.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/15 21:06:33 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/07/17 13:09:30 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstr_uni(wchar_t *s)
{
	size_t i;

	i = 0;
	while (s[i])
	{
		ft_putwchar_t(s[i]);
		i++;
	}
}

void	ft_aux2(unsigned int v)
{
	unsigned char	bits;
	unsigned int	mask;
	unsigned char	byte;

	mask = 49280;
	bits = ((v >> 6) << 27) >> 27;
	byte = (mask >> 8) | bits;
	ft_putchar(byte);
	bits = (v << 26) >> 26;
	byte = ((mask << 24) >> 24) | bits;
	ft_putchar(byte);
}

void	ft_aux3(unsigned int v)
{
	unsigned char	bits;
	unsigned int	mask;
	unsigned char	byte;

	mask = 14712960;
	bits = ((v >> 12) << 28) >> 28;
	byte = (mask >> 16) | bits;
	ft_putchar(byte);
	bits = ((v >> 6) << 26) >> 26;
	byte = ((mask << 16) >> 24) | bits;
	ft_putchar(byte);
	bits = (v << 26) >> 26;
	byte = ((mask << 24) >> 24) | bits;
	ft_putchar(byte);
}

void	ft_aux4(unsigned int v)
{
	unsigned char	bits;
	unsigned int	mask;
	unsigned char	byte;

	mask = 4034953344;
	bits = ((v >> 18) << 29) >> 29;
	byte = (mask >> 24) | bits;
	ft_putchar(byte);
	bits = ((v >> 12) << 26) >> 26;
	byte = ((mask << 8) >> 24) | bits;
	ft_putchar(byte);
	bits = ((v >> 6) << 26) >> 26;
	byte = ((mask << 16) >> 24) | bits;
	ft_putchar(byte);
	bits = (v << 26) >> 26;
	byte = ((mask << 24) >> 24) | bits;
	ft_putchar(byte);
}

void	ft_putwchar_t(wchar_t w)
{
	unsigned int n;

	n = (unsigned int)w;
	if (ft_count_bits(n) <= 7)
		ft_putchar((char)n);
	else if (ft_count_bits(n) <= 11)
		ft_aux2(n);
	else if (ft_count_bits(n) <= 16)
		ft_aux3(n);
	else
		ft_aux4(n);
}
