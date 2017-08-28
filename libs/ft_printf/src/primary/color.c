/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 21:02:04 by Philippe          #+#    #+#             */
/*   Updated: 2017/05/23 20:05:10 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_color.h"
#include "util.h"
#include <stdlib.h>

static int	is_color(char color[8])
{
	int i;

	i = 0;
	while (i < 57)
	{
		if (!ft_strcmp(color, g_color_tab[i].str))
			return (1);
		i++;
	}
	return (0);
}

static int	put_color(char color[8], int put(int c))
{
	int		i;
	char	*tmp;

	i = 0;
	while (i < 57)
	{
		if (!ft_strcmp(color, g_color_tab[i].str))
		{
			tmp = g_color_tab[i].code;
			while (*tmp)
			{
				put(*tmp);
				tmp++;
			}
		}
		i++;
	}
	return (1);
}

int			do_color(const char **fmt, int put(int c))
{
	int		i;
	char	color[MAX_COLOR + 1];

	if (**fmt != '{')
		return (0);
	i = 0;
	(*fmt)++;
	while (i < MAX_COLOR)
		color[i++] = '\0';
	i = 0;
	while (**fmt && **fmt != '}' && i < MAX_COLOR)
		color[i++] = *(*fmt)++;
	if (**fmt != '}' || !is_color(color))
	{
		put('{');
		(*fmt) -= i;
		return (0);
	}
	else
	{
		(*fmt)++;
		put_color(color, put);
		return (1);
	}
}
