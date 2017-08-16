/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 12:45:22 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/05/29 14:47:07 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned int	i;
	char			*answer;
	unsigned char	c_p;

	i = 0;
	c_p = (unsigned char)c;
	answer = (char *)str;
	while (i < n)
	{
		answer[i] = c_p;
		i++;
	}
	return (answer);
}
