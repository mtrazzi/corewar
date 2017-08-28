/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 16:07:15 by pkirsch           #+#    #+#             */
/*   Updated: 2017/08/28 16:31:24 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*strnew;
	size_t	index;

	strnew = (char *)malloc(sizeof(char) * (len + 1));
	if (!strnew)
		return (NULL);
	strnew[len] = '\0';
	index = 0;
	while (index < len)
	{
		strnew[index] = s[index + start];
		++index;
	}
	return (strnew);
}
