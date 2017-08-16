/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 12:45:56 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/05/27 12:58:57 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*ans;

	ans = (char *)s;
	i = ft_strlen(ans) - 1;
	if (c == 0)
		return (ans + i + 1);
	while (i >= 0 && ans[i] != c)
		i--;
	if (i >= 0)
		return (ans + i);
	return (NULL);
}
