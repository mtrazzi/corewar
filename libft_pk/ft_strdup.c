/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 17:11:51 by pkirsch           #+#    #+#             */
/*   Updated: 2017/08/23 17:29:34 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "util.h"

char	*ft_strdup(const char *s1)
{
	size_t	size;
	char	*dst;

	size = ft_strlen(s1);
	if (!(dst = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	dst = ft_strcpy(dst, s1);
	return (dst);
}
