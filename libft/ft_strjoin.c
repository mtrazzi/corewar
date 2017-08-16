/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 16:37:43 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/08/14 09:13:13 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	size_t	i;

	i = 0;
	if (!(s1))
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	if (!(dst = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		exit(EXIT_FAILURE);
	while (i < ft_strlen(s1))
	{
		dst[i] = s1[i];
		i++;
	}
	while (i - ft_strlen(s1) < ft_strlen(s2))
	{
		dst[i] = s2[i - ft_strlen(s1)];
		i++;
	}
	return (dst);
}
