/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 12:45:54 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/06/01 13:48:15 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	i;
	size_t	j;
	char	*str;

	str = (char *)haystack;
	i = 0;
	while (str[i] && i < n)
	{
		j = 0;
		while (needle[j] && needle[j] == str[i + j] && i + j < n)
			j++;
		if (j == ft_strlen(needle))
			return (str + i);
		i++;
	}
	return (NULL);
}
