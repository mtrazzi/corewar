/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 18:30:59 by pkirsch           #+#    #+#             */
/*   Updated: 2017/09/28 18:38:42 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	skip_whitespaces(char **str)
{
	if (!str || !*str)
		return ;
	while (**str && ft_iswithespace(**str))
		(*str)++;
}

void	skip_to_whitespaces(char **str)
{
	if (!str || !*str)
		return ;
	while (**str && !ft_iswithespace(**str))
		(*str)++;
}

char	*get_next_whitespace(char *str)
{
	if (!str)
		return (NULL);
	while (*str && !ft_iswithespace(*str))
		str++;
	return (str);
}

void	skip_to(char **str, char c)
{
	if (!str || !*str)
		return ;
	while (**str && **str != c)
		(*str)++;
}

char	*get_next(char *str, char c)
{
	if (!str)
		return (NULL);
	while (*str && *str != c)
		str++;
	return (str);
}
