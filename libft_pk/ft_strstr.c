/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 19:05:31 by pkirsch           #+#    #+#             */
/*   Updated: 2017/06/04 20:13:11 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

char	*ft_strstr(const char *big, const char *little)
{
	int i;
	int j;

	if (little[0] == '\0')
		return ((char *)big);
	i = 0;
	while (big[i])
	{
		if (big[i] == little[0])
		{
			j = 0;
			while (little[j])
			{
				if (big[i + j] != little[j])
					break ;
				++j;
			}
			if (little[j] == '\0')
				return ((char *)(big + i));
		}
		++i;
	}
	return (NULL);
}
