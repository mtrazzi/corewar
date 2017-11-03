/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 18:05:03 by pkirsch           #+#    #+#             */
/*   Updated: 2017/11/03 19:07:15 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

#define BAD_N ("bad usage of option 'n'")
#define BAD_V ("bad usage of option 'v'")
#define BAD_D ("bad usage of option 'dump'")
#define NO_CHAMPION ("no champion found")

t_opts g_opts[] =
{
	{'d', "dump", 1, {{0, NULL}}, OPT_D, OPT_V | OPT_M | OPT_A},
	{'n', NULL, 2, {{0, NULL}, {0, NULL}}, OPT_N, 0},
	{'n', NULL, 2, {{0, NULL}, {0, NULL}}, OPT_N, 0},
	{'n', NULL, 2, {{0, NULL}, {0, NULL}}, OPT_N, 0},
	{'n', NULL, 2, {{0, NULL}, {0, NULL}}, OPT_N, 0},
	{'v', NULL, 1, {{0, NULL}}, OPT_V, OPT_D | OPT_A | OPT_M},
	{'m', NULL, 0, {{0, NULL}}, OPT_M, OPT_D | OPT_V | OPT_A},
	{'a', NULL, 0, {{0, NULL}}, OPT_A, OPT_D | OPT_V | OPT_M},//to activate
	{0, 0, 0, {{0, NULL}}, 0, 0}
};

t_prog_param g_prog_param[] =
{
	{".cor", REST_END, 'n', 1}, //| REST_EQUAL
	{NULL, 0, 0, 0}
};



int		check_n(t_opts *opts, t_env *e)
{
	static int chp_nb = 0;
	// if (opts->params[0].arg == NULL)//[1]
		// return (1);
	if (is_empty_op(opts))
		return (1);
	if (opts->params[0].arg && ft_isdigits_str(opts->params[0].arg) == 0)
		return (ft_error(BAD_N));
	opts->params[0].value = opts->params[0].arg ? ft_atoi(opts->params[0].arg) : --chp_nb;
	if (is_valid_ext(opts->params[1].arg) == 0
		|| ft_parse_chp(e, opts->params[1].arg, opts->params[0].value) < 0)
		return (ft_error(BAD_N));
	return (1);
}

int		check_dump_v(t_opts *opts, t_env *e)
{
	if (ft_isdigits_str(opts->params[0].arg) == 0)
		return (opts->id == 'd' ? ft_error(BAD_D) : ft_error(BAD_V));
	opts->params[0].value = ft_atoi(opts->params[0].arg);
	if (opts->id == 'd')
		e->par.dump_cycle = opts->params[0].value;
	else
		e->par.opts |= (opts->params[0].value & (OPT_V1 | OPT_V2 | OPT_V4 | OPT_V8 | OPT_V16));
	return (1);
}

int		check_opt(t_env *e)
{
	int	k;

	k = -1;
	while (g_opts[++k].id)
		if ((g_opts[k].on & e->par.opts)
				&& (g_opts[k].id == 'v' || g_opts[k].id == 'd')
				&& check_dump_v(&g_opts[k], e) < 0)
			return (-1);
		else if ((g_opts[k].on & e->par.opts) && g_opts[k].id == 'n'
					&& check_n(&g_opts[k], e) < 0)
			return (-1);
		else if ((g_opts[k].on & e->par.opts) && g_opts[k].id == 'm')
			e->par.opts |= OPT_M;
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
ft_printf("i: %d\n", i);
	if (i < 0)
		return (usage());
	if (check_opt(e) < 0)
		return (usage());
	if (!(e->par.opts & OPT_N) && i >= ac)
		return (error_usage(NO_CHAMPION));
	while (i < ac)
		return (ft_error("OYOYO\n"));
		// if (!is_valid_ext(av[i]) || ft_parse_chp(e, av[i++], --chp_nb) < 0)
		// 	return (usage());
	return (0);
}
