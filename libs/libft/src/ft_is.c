/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 18:39:35 by pkirsch           #+#    #+#             */
/*   Updated: 2017/09/28 18:39:49 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_iswithespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\f' || c == '\r');
}
