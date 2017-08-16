/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 12:44:50 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/05/27 12:55:51 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned int	i;
	char			*answer;

	i = 0;
	answer = (char*)s;
	while (i < n)
	{
		answer[i] = '\0';
		i++;
	}
	s = (void *)answer;
}
