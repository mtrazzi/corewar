/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 12:45:02 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/05/29 12:35:56 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned int	i;
	char			*s;
	char			*d;
	unsigned char	c_p;

	i = 0;
	s = (char *)src;
	d = (char *)dest;
	c_p = (unsigned char)c;
	while (i < n)
	{
		d[i] = s[i];
		i++;
		if (s[i - 1] == c_p)
			return (dest + i);
	}
	return (NULL);
}
