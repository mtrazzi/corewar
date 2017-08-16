/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pfutils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/06 14:04:59 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/08/06 14:05:04 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_insert_plus(char *str)
{
	char	*dest;
	size_t	i;

	i = 0;
	dest = ft_strdup(str);
	while (str[i] == ' ')
		i++;
	dest[i - 1] = '+';
	return (dest);
}

char	*ft_insert_minus(char *str)
{
	char	*dest;
	size_t	i;

	i = 0;
	dest = ft_strdup(str);
	while (str[i] == ' ')
		i++;
	dest[i - 1] = '-';
	return (dest);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*temp;
	size_t	i;

	i = 0;
	if ((temp = (char *)malloc(sizeof(char) * (n + 1))) == NULL)
		exit(EXIT_FAILURE);
	while (i < n && s[i])
	{
		temp[i] = s[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

int		ft_count_bits(unsigned int n)
{
	if (n == 0 || n == 1)
		return (1);
	return (ft_count_bits(n / 2) + 1);
}
