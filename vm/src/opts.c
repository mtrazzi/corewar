/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 19:34:48 by pkirsch           #+#    #+#             */
/*   Updated: 2017/11/02 19:36:40 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "opts.h"

/*
**	same_empty_opt
**	added to handle '-n number' option in corewar [added for option with param]
**	TODO: stop if already parsed opt? (needed for corewar -n option)?
*/

static int	same_empty_opt(int j, int id)
{
	int tmp;

	tmp = j;
	if (g_opts[j].nb_param == 0)
		return (j);
	if (g_opts[j].params[0].arg == NULL)
		return (j);
	while (g_opts[++j].id)
		if (g_opts[j].id == id && g_opts[j].params[0].arg == NULL)
		{
			if (g_opts[tmp].str != NULL &&
				ft_strncmp(g_opts[tmp].str, g_opts[j].str,
							ft_strlen(g_opts[tmp].str)) != 0)
				continue ;
			return (j);
		}
	return (-1);
}

static int	ft_getparams(int ac, char **av, int ac_index, int *used_args,
							t_opts *opt)
{
	int		i;

	i = -1;
	while (++i < opt->nb_param && ac - (ac_index + *used_args + 1) > 0)
	{
		if (av[ac_index + *used_args + 1][0] == '-')
			break ;
		opt->params[i].arg = av[ac_index + *used_args + 1];
		*used_args += 1;
	}
	if (opt->nb_param && opt->params[opt->nb_param - 1].arg == NULL)
		return (ft_error(OPT_NOT_ENOUGH_PARAM));
	return (opt->nb_param);
}

static int	update_g_opts(u_int *opts, char **av, int *ac_index, int *i)
{
	int	j;
	int	is_opt;

	is_opt = 0;
	j = -1;
	while (g_opts[++j].id)
		if (g_opts[j].id == av[*ac_index][*i])
		{
			if (g_opts[j].str != NULL &&
					ft_strncmp(g_opts[j].str, av[*ac_index] + *i,
								ft_strlen(g_opts[j].str)) != 0)
				continue ;
			j = same_empty_opt(j, g_opts[j].id);
			if (j < 0)
				return (ft_error(OPT_REPEAT));
			*i += g_opts[j].str != NULL ? ft_strlen(g_opts[j].str) : 1;
			if (*opts & g_opts[j].off)
				return (ft_error(OPT_COLLISION));
			*opts |= g_opts[j].on;
			is_opt = 1;
			break ;
		}
	if (!is_opt)
		return (ft_error(OPT_NOT));
	return (j);
}

static int	ft_getopts(int ac, char **av, int *ac_index, u_int *opts)
{
	int		i;
	int		j;
	int		used_args;

	used_args = 0;
	i = 1;
	while (av[*ac_index][i])
	{
		if ((j = update_g_opts(opts, av, ac_index, &i)) < 0)
			return (-1);
		if (ft_getparams(ac, av, *ac_index, &used_args, &g_opts[j]) < 0)
			return (-1);
	}
	*ac_index += used_args;
	return (1);
}

int			parse_params(int ac, char **av, u_int *opts)
{
	int found_non_opt;
	int	i;

	found_non_opt = 0;
	i = 0;
	while (++i < ac)
		if (av[i][0] == '-')
		{
			if (found_non_opt != 0)
				return (ft_error(OPT_AFTER_ARG));
			if (!av[i][1])
				break ;
			if (ft_getopts(ac, av, &i, opts) < 0)
				return (-1);
		}
		else
			found_non_opt += 1;
	i = i - found_non_opt;
	return (i);
}
