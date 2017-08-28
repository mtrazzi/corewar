/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uni_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 18:40:28 by pkirsch           #+#    #+#             */
/*   Updated: 2017/05/19 18:40:36 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		most_significant_bit_position_u(unsigned int n)
{
	int				count;
	unsigned int	i;

	if (!n)
		return (0);
	i = 0x80000000;
	while (!(n & i))
		i >>= 1;
	count = 0;
	while (i > 0)
	{
		count++;
		i >>= 1;
	}
	return (count);
}
