/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parsing_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 18:32:15 by pkirsch           #+#    #+#             */
/*   Updated: 2017/09/29 15:27:03 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	init_t_parse(t_parse *p, t_asm *a)
{
	p->sym_curr = a->syms;
	p->to_skip_curr = a->to_skip_syms;
	p->line_count = 0;
	p->add_line_start = NULL;
	p->alc = NULL;
}

char	*get_next_separator(char *str)
{
	if (!str)
		return (NULL);
	while (*str && *str != SEPARATOR_CHAR)
		str++;
	return (str);
}

int		is_com(char *str)
{
	if (str && (*str == COMMENT_CHAR || *str == COMMENT_CHAR2))
		return (1);
	return (0);
}

int		ft_atoi_mod(const char *str)//
{
	int		i;
	long	number;
	int		is_negative;

	i = 0;
	number = 0;
	is_negative = 1;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n' ||
		str[i] == '\r' || str[i] == '\t' || str[i] == '\v')
		++i;
	if (str[i] == '+' || str[i] == '-')
	{
		is_negative = (str[i] == '-') ? -1 : 1;
		++i;
	}
	while (str[i] >= '0' && str[i] <= '9')
		number = number * 10 + (str[i++] - 48);
	number *= is_negative;
	return ((int)number);
}

int		free_str(char **str)
{
	if (!str && !*str)
		free(*str);
	*str = NULL;
	return (1);
}
