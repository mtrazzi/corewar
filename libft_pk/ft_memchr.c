/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 17:00:02 by pkirsch           #+#    #+#             */
/*   Updated: 2017/06/04 20:12:46 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char *c_s;

	c_s = s;
	while (n--)
	{
		if (*c_s == (unsigned char)c)
			return ((void *)c_s);
		++c_s;
	}
	return (NULL);
}
