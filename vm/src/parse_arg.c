/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 11:55:15 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/09/10 13:10:32 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

#define STR_ERR_NB_CHP "too many champions"

static char		*usage(void)
{
	return ("usage: corewar [-v N | -m][-dump nbr_cycles] \
			[[-n number] champion1.cor] ...");
}

static int		is_valid_ext(char *file_name)
{
	return (!ft_strcmp(file_name + (ft_strlen(file_name) - 4), ".cor"));
}

static int		ft_parse_chp(t_env *e, char *file_name, int chp_nb)
{
	t_chp new_chp;

	if (++(e->par.nb_chp) > MAX_PLAYERS)
		return (ft_error_vm(STR_ERR_NB_CHP));
	new_chp.nb = chp_nb;
	new_chp.file_name = file_name;
	e->par.champions[e->par.nb_chp - 1] = new_chp;
	return (0);
}

int				ft_check_option(t_env *e, int i, int ac, char **av)
{
	if ((ft_strcmp(av[i] + 1, "dump") && ft_strcmp(av[i] + 1, "n") &&
		ft_strcmp(av[i] + 1, "m") && ft_strcmp(av[i] + 1, "v")) || i + 1 >= ac)
		return (-1);
	if (!ft_strcmp(av[i] + 1, "dump"))
	{
		e->par.dump += 1;
		if (!ft_is_int(av[i + 1]) || e->par.dump > 1)
			return (-1);
		e->par.nb_cyc = ft_atoi(av[i + 1]);
		return (1);
	}
	else if (!ft_strcmp(av[i] + 1, "m"))
		e->par.print = 1;
	else if (!ft_strcmp(av[i] + 1, "v"))
	{
		e->par.verb = ft_atoi(av[i + 1]);
		return (1);
	}
	else if (!ft_strcmp(av[i] + 1, "n"))
		return ((!ft_is_int(av[i + 1]) || i + 2 >= ac ||
		!is_valid_ext(av[i + 2]) || (ft_parse_chp(e, av[i + 2],
		ft_atoi(av[i + 1])) < 0)) ? -1 : 2);
	return (0);
}

int				parse_arg_vm(int ac, char **av, t_env *e)
{
	int			i;
	int			ret;
	static	int	chp_nb = 0;

	if (ac < 2)
		return (ft_error_vm(usage()));
	i = 1;
	while (i < ac)
	{
		if (av[i][0] == '-')
		{
			if ((ret = ft_check_option(e, i, ac, av)) < 0)
				return (ft_error_vm(usage()));
			i += ret;
		}
		else if (!is_valid_ext(av[i]) || ft_parse_chp(e, av[i], --chp_nb) < 0)
			return (ft_error_vm(usage()));
		i++;
	}
	e->last_alive = e->par.champions[e->par.nb_chp - 1].nb;
	return (0);
}
