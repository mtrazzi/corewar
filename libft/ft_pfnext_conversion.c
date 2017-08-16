/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_next_conversion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 16:00:50 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/07/17 13:09:19 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_is_conversion(char c)
{
	if (c == 's' || c == 'S' || c == 'p' || c == 'd' || c == 'D')
		return (1);
	else if (c == 'i' || c == 'o' || c == 'O' || c == 'u' || c == 'U')
		return (1);
	else
		return (c == 'x' || c == 'X' || c == 'c' || c == 'C' || c == '%');
}

char	ft_next_conversion(const char *str)
{
	int i;

	i = 0;
	while (str[i] && !(ft_is_conversion(str[i])))
		i++;
	return (str[i]);
}
