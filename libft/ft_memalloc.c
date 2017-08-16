/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 14:53:04 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/07/24 19:19:01 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char	*ans;

	if ((ans = (char *)malloc(size)) == 0)
		exit(EXIT_FAILURE);
	ft_bzero(ans, size);
	return (ans);
}
