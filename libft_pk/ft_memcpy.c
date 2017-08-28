/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 15:57:50 by pkirsch           #+#    #+#             */
/*   Updated: 2017/06/04 20:13:58 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*c_dst;
	const unsigned char	*c_src;

	c_dst = dst;
	c_src = src;
	while (n--)
	{
		*c_dst = *c_src;
		++c_dst;
		++c_src;
	}
	return (dst);
}
