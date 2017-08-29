#include "vm.h"

# define STR_ERR_USAGE	"usage: corewar [-dump nbr_cycles] \
[[-n number] champion1.cor] ..."
# define STR_ERR_NB_CHP "too many champions"

static int		ft_is_valid_ext(char *file_name)
{
	while (*file_name != '.')
		file_name++;
	return (!ft_strcmp(file_name, ".cor"));
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

int		ft_check_option(t_env *e, int i, int ac, char **av)
{
	if ((ft_strcmp(av[i] + 1, "dump") && ft_strcmp(av[i] + 1, "n")) || \
		i + 1 >= ac)
		return (-1);
	if (!ft_strcmp(av[i] + 1, "dump"))
	{
		e->par.dump += 1;
		if (!ft_is_int(av[i + 1]) || e->par.dump > 1)
			return(-1);
		e->par.nb_cyc = ft_atoi(av[i + 1]);
	}
	else if (!ft_strcmp(av[i] + 1, "n"))
	{
		if (!ft_is_int(av[i + 1]) || i + 2 >= ac || !ft_is_valid_ext(av[i + 2]))
				return (-1);
		if (ft_parse_chp(e, av[i], ft_atoi(av[i + 2]) < 0))
				return (-1);
		return (2);
	}
	return (1);
}

int		parse_arg_vm(int ac, char **av, t_env *e)
{
	int i;
	int ret;
	static int chp_nb = 0;

	if (ac < 2)
		return (ft_error_vm(STR_ERR_USAGE));
	i = 1;
	while (i < ac)
	{
		if (av[i][0] == '-')
		{
			if ((ret = ft_check_option(e, i, ac, av)) < 0)
				return (ft_error_vm(STR_ERR_USAGE));
			i += ret;
		}
		else if (!ft_is_valid_ext(av[i]) || ft_parse_chp(e, av[i], --chp_nb) < 0)
			return (ft_error_vm(STR_ERR_USAGE));
		i++;
	}
	return (0);
}
