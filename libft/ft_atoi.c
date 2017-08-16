/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/06 13:59:48 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/08/06 14:00:06 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_atoi(const char *nptr)
{
	int					s;
	int					i;
	unsigned long long	nb;

	i = 0;
	s = 1;
	nb = 0;
	while (nptr[i] == ' ' || nptr[i] == '\n' || \
nptr[i] == '\v' || nptr[i] == '\r' || nptr[i] == '\t' || nptr[i] == '\f')
		i++;
	if (nptr[i] == '-')
		s = -1;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (48 <= nptr[i] && nptr[i] <= 57)
	{
		nb = 10 * nb + nptr[i] - 48;
		i++;
	}
	if (nb > 9223372036854775807 && s == -1)
		return (0);
	if (nb > 9223372036854775807 && s == 1)
		return (-1);
	return ((int)(s * nb));
}
