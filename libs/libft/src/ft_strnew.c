/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 15:21:57 by pkirsch           #+#    #+#             */
/*   Updated: 2017/09/02 20:37:47 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*strnew;

	strnew = (char *)malloc(sizeof(char) * (size + 1));
	if (!strnew)
		return (NULL);
	strnew[size] = '\0';
	while (size)
		strnew[--size] = '\0';
	strnew[size] = '\0';
	return (strnew);
}
