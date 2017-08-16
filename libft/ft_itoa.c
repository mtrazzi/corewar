/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/15 19:41:07 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/08/06 14:01:49 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t			num_dig(long long n)
{
	size_t m;

	m = 1;
	while (n > 9)
	{
		n /= 10;
		m++;
	}
	return (m);
}

static char				*ft_itoa_aux(long long n, char *s, int len, int i)
{
	while (--len >= 0)
	{
		s[len] = '0' + n % 10;
		n /= 10;
	}
	return (s - i);
}

char					*ft_itoa(long long n)
{
	char *tmp;

	if (n == LLONG_MIN)
	{
		if ((tmp = ft_strnew(sizeof(char) * 20)) == NULL)
			return (NULL);
		return (ft_strncpy(tmp, "-9223372036854775808", 20));
	}
	if (n < 0)
	{
		if ((tmp = ft_strnew(num_dig(-n) + 1)) == NULL)
			return (NULL);
		tmp[0] = '-';
		return (ft_itoa_aux(-n, tmp + 1, num_dig(-n), 1));
	}
	if ((tmp = ft_strnew(sizeof(char) * num_dig(n))) == NULL)
		return (NULL);
	return (ft_itoa_aux(n, tmp, num_dig(n), 0));
}
