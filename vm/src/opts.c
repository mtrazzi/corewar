#include "opts.h"

static int	ft_getparams(int ac, char **av, int ac_index, int *used_args,
							t_opts *opt)
{
	int		i;

	i = -1;
	while (++i < opt->nb_param && ac - (ac_index + *used_args + 1) > 0)
	{
			if (av[ac_index + *used_args + 1][0] == '-')
				return (-1);
			opt->params[i].arg = av[ac_index + *used_args + 1];
			*used_args += 1;
	}
	return (opt->nb_param);
}

static int	ft_getopts(int ac, char **av, int *ac_index, u_int *opts)
{
	int		i;
	int		j;
	int		is_opt;
	int		used_args;

	used_args = 0;
	i = 1;
	while (av[*ac_index][i])
	{
		is_opt = 0;
		j = -1;
		while (g_opts[++j].id)
			if (g_opts[j].id == av[*ac_index][i])
			{
				if (g_opts[j].str != NULL && strncmp(g_opts[j].str, av[*ac_index] + i, strlen(g_opts[j].str)) != 0)//
					continue ;
				i += g_opts[j].str != NULL ? strlen(g_opts[j].str) : 1;//
				*opts &= ~g_opts[j].off;
				*opts |= g_opts[j].on;
				is_opt = 1;
				break ;
			}
		if (!is_opt)
			return (-1);
		ft_getparams(ac, av, *ac_index, &used_args, &g_opts[j]);
	}
	*ac_index += used_args;
	return (1);
}

int			parse_params(int ac, char **av, u_int *opts)
{
	int	i;
	int j;
	int k;

	i = 0;
	while (++i < ac)
		if (av[i][0] == '-')
		{
			if (!av[i][1])
				break ;
			if (ft_getopts(ac, av, &i, opts) < 0)
				return (-1);
		}
		else
			break ;
	j = -1;
	while (g_opts[++j].id)
	{
		k = -1;
		while (++k < g_opts[j].nb_param && g_opts[j].on & *opts)
			if (g_opts[j].params[k].arg == NULL)
				return (-1);
	}
	return (i);//-1
}
