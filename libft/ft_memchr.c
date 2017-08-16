/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 12:45:09 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/05/31 18:56:26 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned int	i;
	unsigned char	c_p;

	str = (unsigned char *)s;
	c_p = (unsigned char)c;
	i = 0;
	while (i < n && str[i] != c_p)
		i++;
	if (i == n)
		return (NULL);
	return (str + i);
}
