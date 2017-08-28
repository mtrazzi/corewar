/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min_max.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 23:59:38 by pkirsch           #+#    #+#             */
/*   Updated: 2017/07/20 23:59:50 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_min(int a, int b)
{
	return (a < b ? a : b);
}

int		ft_max(int a, int b)
{
	return (a > b ? a : b);
}
