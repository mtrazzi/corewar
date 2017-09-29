/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endian_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 18:48:02 by pkirsch           #+#    #+#             */
/*   Updated: 2017/09/29 15:32:03 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static u_int	convert_to_be(u_int n)
{
	u_int tmp;

	tmp = 0;
	tmp = (0x000000ff & n) << 24;
	tmp |= (0x0000ff00 & n) << 8;
	tmp |= (0x00ff0000 & n) >> 8;
	tmp |= (0xff000000 & n) >> 24;
	return (tmp);
}

void			ft_print_hexa(u_int n)
{
	uint32_t b0;
	uint32_t b1;
	uint32_t b2;
	uint32_t b3;

	b0 = (0x000000ff & n);
	b1 = (0x0000ff00 & n) >> 8;
	b2 = (0x00ff0000 & n) >> 16;
	b3 = (0xff000000 & n) >> 24;
	ft_printf("|%x %x %x %x|\n", b3, b2, b1, b0);
}

/*
** Write in big endian
*/

void			write_be(int fd, u_int n, u_int size)//PASSER EN INT?
{
	u_int	k;
	char	*s;

	k = convert_to_be(n);
	s = (char *)&k;
	write(fd, s + (4 - size), size); //
}
