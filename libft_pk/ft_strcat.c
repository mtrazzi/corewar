/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 18:12:31 by pkirsch           #+#    #+#             */
/*   Updated: 2017/06/04 19:55:14 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

char	*ft_strcat(char *s1, const char *s2)
{
	char	*tmp;

	tmp = s1;
	while (*s1)
		++s1;
	while (*s2)
	{
		*s1 = *s2;
		++s1;
		++s2;
	}
	*s1 = '\0';
	return (tmp);
}
