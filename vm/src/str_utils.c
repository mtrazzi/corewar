/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 15:28:50 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/09/10 15:38:01 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

#define B0 0x000000ff
#define B1 0x0000ff00
#define B2 0x00ff0000
#define B3 0xff000000

u_int	convert_uint(u_int n)
{
	return ((n & B0) << 24 | (n & B1) << 8 | (n & B2) >> 8
			| (n & B3) >> 24);
}

int		convert_4_bytes(u_char b0, u_char b1, u_char b2, u_char b3)
{
	return (((int)b0) << 24 | ((int)b1) << 16 | ((int)b2) << 8 | \
			((int)b3));
}

short	convert_2_bytes(u_char b0, u_char b1)
{
	return ((short)(((int)b0) << 8 | ((int)b1)));
}

void	clear_screen(void)
{
	printf("\033[2J");
}

int		dump(t_env *e)
{
	int i;
	int j;

	i = 0;
	while (i < MEM_SIZE)
	{
		printf("0x%04x : ", i);
		j = -1;
		while (++j < 64)
			printf("%02x ", e->map[i + j]);
		printf("\n");
		i += 64;
	}
	return (0);
}
