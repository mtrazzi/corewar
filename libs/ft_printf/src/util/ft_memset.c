/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 15:40:00 by pkirsch           #+#    #+#             */
/*   Updated: 2017/05/23 20:09:27 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*c_b;

	c_b = (unsigned char *)b;
	while (len--)
	{
		*c_b = (unsigned char)c;
		++c_b;
	}
	return (b);
}
