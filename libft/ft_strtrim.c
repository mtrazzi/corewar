/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 16:54:46 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/06/01 17:20:13 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_over(char const *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (!(s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
			return (0);
		i++;
	}
	return (1);
}

char		*ft_strtrim(char const *s)
{
	char	*dst;
	size_t	i;
	size_t	c;

	if (s == NULL)
		return (NULL);
	i = 0;
	c = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	while (!is_over(s + i))
	{
		i++;
		c++;
	}
	if ((dst = ft_strnew(c)) == NULL)
		return (NULL);
	return (ft_strncpy(dst, s + i - c, c));
}
