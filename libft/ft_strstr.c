/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 12:46:00 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/06/01 16:12:11 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	j;
	char	*str;

	str = (char *)haystack;
	i = 0;
	if (*needle == '\0')
		return (str);
	while (str[i])
	{
		j = 0;
		while (needle[j] && needle[j] == str[i + j])
			j++;
		if (j == ft_strlen(needle))
			return (str + i);
		i++;
	}
	return (NULL);
}
