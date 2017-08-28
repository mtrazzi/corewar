/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_power_long_double.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 18:16:59 by pkirsch           #+#    #+#             */
/*   Updated: 2017/05/19 18:19:02 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long double		iterative_power_long_double(long double nb, int power)
{
	int			i;
	long double	result;

	i = 0;
	result = 1;
	if (power < 0)
		return (0);
	else if (power == 0)
		return (result);
	while (i < power)
	{
		result *= nb;
		i++;
	}
	return (result);
}
