/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uni.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 13:53:02 by pkirsch           #+#    #+#             */
/*   Updated: 2017/05/22 21:30:17 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cvt.h"

static void		uni_8(int c, int put(int c))
{
	int tmp;

	tmp = 0xC0 | (0x1F & (c >> 6));
	put(tmp);
	tmp = 0x80 | (0x3F & c);
	put(tmp);
}

static void		uni_16(int c, int put(int c))
{
	int tmp;

	tmp = 0xE0 | (0xF & (c >> 12));
	put(tmp);
	tmp = 0x80 | (0x3F & (c >> 6));
	put(tmp);
	tmp = 0x80 | (0x3F & c);
	put(tmp);
}

static void		uni_32(int c, int put(int c))
{
	int tmp;

	tmp = 0xF0 | (0x7 & (c >> 18));
	put(tmp);
	tmp = 0x80 | (0x3F & (c >> 12));
	put(tmp);
	tmp = 0x80 | (0x3F & (c >> 6));
	put(tmp);
	tmp = 0x80 | (0x3F & c);
	put(tmp);
}

static int		uni_x(int bc, int c, int put(int c))
{
	if (bc <= 7)
	{
		put(c);
		return (1);
	}
	else if (bc <= 11)
	{
		uni_8(c, put);
		return (2);
	}
	else if (bc <= 16)
	{
		uni_16(c, put);
		return (3);
	}
	else
	{
		uni_32(c, put);
		return (4);
	}
}

int				uni(int c, int put(int c))
{
	int		bc;

	if (c < 0)
		return (-1);
	if (MB_CUR_MAX == 1 && (c >= 0 && c <= 255))
	{
		put((unsigned char)c);
		return (1);
	}
	else if (MB_CUR_MAX == 1)
		return (-1);
	bc = most_significant_bit_position_u(c);
	if (bc <= 21)
		return (uni_x(bc, c, put));
	return (-1);
}
