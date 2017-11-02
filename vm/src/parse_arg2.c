/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 18:05:03 by pkirsch           #+#    #+#             */
/*   Updated: 2017/09/10 19:17:29 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

# define BAD_N "bad usage of option 'n'"
# define BAD_V "bad usage of option 'v'"
# define BAD_D "bad usage of option 'dump'"
# define NO_CHAMPION "no champion found"

t_opts g_opts[] = 
{
	{'d', "dump", 1, {{0, NULL}}, OPT_D, OPT_V | OPT_M | OPT_A},
	{'n', NULL, 2, {{0, NULL}, {0, NULL}}, OPT_N, 0},
	{'n', NULL, 2, {{0, NULL}, {0, NULL}}, OPT_N, 0},
	{'n', NULL, 2, {{0, NULL}, {0, NULL}}, OPT_N, 0},
	{'n', NULL, 2, {{0, NULL}, {0, NULL}}, OPT_N, 0},
	{'v', NULL, 1, {{0, NULL}}, OPT_V, OPT_D | OPT_A | OPT_M},
	{'m', NULL, 0, {}, OPT_M, OPT_D | OPT_V | OPT_A},
	{'a', NULL, 0, {}, OPT_A, OPT_D | OPT_V | OPT_M},
	{0, 0, 0, {}, 0, 0}
};

int		check_n(t_opts *opts, t_env *e)
{
	if (opts->params[0].arg == NULL)
		return (1);
	if (ft_isdigits_str(opts->params[0].arg) == 0)
		return (ft_error(BAD_N));
	opts->params[0].value = ft_atoi(opts->params[0].arg);//change atoi, use mine
	if (is_valid_ext(opts->params[1].arg) == 0 || ft_parse_chp(e, opts->params[1].arg, opts->params[0].value) < 0)
		return (ft_error(BAD_N));
	return (1);
}

int		check_dump_v(t_opts *opts, t_env *e)
{
	if (ft_isdigits_str(opts->params[0].arg) == 0)
		return (opts->id == 'd' ? ft_error(BAD_D) : ft_error(BAD_V));
	opts->params[0].value = ft_atoi(opts->params[0].arg);//change atoi, use mine
	if (opts->id == 'd')
	{
		e->par.dump = 1;//REMOVE
		e->par.nb_cyc = opts->params[0].value;//REANAME TO DUMP
	}
	else
		e->par.verb = opts->params[0].value;//CHANGE
	return (1);
}

int		check_opt(t_env *e)
{
	int	k;

	k = -1;
	while (g_opts[++k].id)
		if ((g_opts[k].on & e->par.opts) && (g_opts[k].id == 'v' || g_opts[k].id == 'd')
				&& check_dump_v(&g_opts[k], e) < 0)
			return (-1);
		else if ((g_opts[k].on & e->par.opts) && g_opts[k].id == 'n'
					&& check_n(&g_opts[k], e) < 0)
			return (-1);
	return (1);
}

int		parse_arg_vm(int ac, char **av, t_env *e)
{
	int		i;
	int		chp_nb;

	chp_nb = 0;
	if (ac < 2)
		return (usage());	
	i = parse_params(ac, av, &e->par.opts);
	if (i < 0)
		return (usage());
	if (check_opt(e) < 0)
		return (usage());
	if (!(e->par.opts & OPT_N) && i >= ac)
		return (error_usage(NO_CHAMPION));
	while (i < ac)
	 	if (!is_valid_ext(av[i]) || ft_parse_chp(e, av[i++], --chp_nb) < 0)
	 		return (usage());
	return (0);
}
