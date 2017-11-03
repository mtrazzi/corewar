/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_champions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 20:39:44 by pkirsch           #+#    #+#             */
/*   Updated: 2017/11/03 21:49:24 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	parse_champ_filename(char *num, char *champ)
{
	int	j;

	if (!is_valid_ext(champ))
		return (-1);
	j = -1;
	while (g_opts[++j].id)
	{
		if (g_opts[j].id == 'n' && is_empty_op(&g_opts[j]))
		{
			g_opts[j].params[0].arg = num;
			g_opts[j].params[1].arg = champ;
			return (1);
		}
	}
	return (ft_error(TOO_MANY_CHAMP));
}

int			parse_champions_file_names(int ac, int *i, char **av, u_int *opts)
{
	while (*i < ac)
		if (av[*i][0] == '-')
		{
			if (ft_strcmp(av[*i], "-n") != 0)
				return (ft_error(OPT_AFTER_ARG));
			if (ac - *i < 3)
				return (ft_error(BAD_N));
			if (parse_champ_filename(av[*i + 1], av[*i + 2]) < 0)
				return (-1);
			if (*opts & (0))
				return (ft_error(OPT_COLLISION));
			*opts |= OPT_N;
			*i += 3;
		}
		else
		{
			if (parse_champ_filename(NULL, av[*i]) < 0)
				return (-1);
			*i += 1;
		}
	return (1);
}
