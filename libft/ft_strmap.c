/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 15:51:18 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/06/01 14:24:32 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*res;
	size_t	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	if ((res = ft_strdup(s)) == NULL)
		return (NULL);
	while (i < ft_strlen(s))
	{
		res[i] = f(res[i]);
		i++;
	}
	return (res);
}
