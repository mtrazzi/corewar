#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
# include <stdio.h>

# define MAX_PARAMS 4
# define FORMAT_LENGTH 16

# define INT_VALUE "int_value"

typedef struct s_opts		t_opts;
typedef struct s_opt_param	t_opt_param;

struct s_opt_param
{
	long	value;//?
	char	*arg;
	// char	format[FORMAT_LENGTH + 1];//rly? -> let the user do it!
	// int		mandatory;
};

struct s_opts
{
	int				id;
	char			*str;
	int				nb_param;
	t_opt_param		params[MAX_PARAMS];
	u_int				on;
	u_int				off;
};

# define OPTS_D 0x00000001
# define OPTS_M 0x00000002
# define OPTS_V 0x00000004


t_opts g_opts[] = 
{
	//(t_opt_param[MAX_PARAMS])
	// {'d', "dump", 1, {{1, NULL, INT_VALUE, 1}}, OPTS_D, OPTS_M | OPTS_V},
	{'d', "dump", 1, {{0, NULL}}, 1, 0},//init all null ?
	{'d', "debris", 3, {{0, NULL}, {0, NULL}, {0, NULL}}, 2, 0},
	{'a', NULL, 0, {}, 4, 0},
	{'b', NULL, 0, {}, 8, 0},
	{'c', NULL, 0, {}, 16, 0},
	{0, 0, 0, {0}, 0, 0}
};

static int	ft_getparams(int ac, char **av, int ac_index, int *used_args,
							t_opts *opt)
{
	int		i;

	i = -1;
	while (++i < opt->nb_param && i < ac - ac_index - *used_args + 1)
	{
			if (av[ac_index + *used_args + 1][0] == '-')
				return (-1);
			opt->params[i].arg = av[ac_index + *used_args + 1];
			printf("_%s_ %d\n", av[ac_index + *used_args + 1], i);
			*used_args += 1;
	}
	return (opt->nb_param);
}

int		ft_getopts(int ac, char **av, int *ac_index, u_int *opts)
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
				if (g_opts[j].str != NULL && strncmp(g_opts[j].str, av[*ac_index] + i, strlen(g_opts[j].str)) != 0)
					continue ;
				i += g_opts[j].str != NULL ? strlen(g_opts[j].str) : 1;
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


int		parse_params(int ac, char **av, u_int *opts)
{
	int	i;
	int j;
	int k;

	i = 0;
	while (++i < ac)// printf("(%s) %u %#010x\n", av[i], *opts, *opts);
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
		while (++k < g_opts[j].nb_param)
			if (g_opts[j].params[k].arg == NULL)
				return (-1);
	}
	return (++i);//
}

int main(int ac, char **av)
{
	int		i;
	u_int	opts = 0;
	// printf("{%c}, {%s}, {%d}, {%#010x}, {%#010x}\n", g_opts[0].id, g_opts[0].str, g_opts[0].nb_param, g_opts[0].on, g_opts[0].off);
	// printf("[%ld] [%s]\n", g_opts[0].params[0].value, g_opts[0].params[0].arg);
	i = parse_params(ac, av, &opts);
	
	int k = -1;
	while (g_opts[++k].id)
	{
		printf("\t{%c}, {%s}, {%d}, {%#010x}, {%#010x}\n", g_opts[k].id, g_opts[k].str, g_opts[k].nb_param, g_opts[k].on, g_opts[k].off);
		int t = -1;
		while (++t < g_opts[k].nb_param)//MAX_PARAMS)//g_opts[k].nb_param)
			printf("\t\tt%d [%ld] [%s]\n", t, g_opts[k].params[t].value, g_opts[k].params[t].arg);
	}
	if (i < 0)
		return (-1);
	printf("%d %#010x\n", opts, opts);
	return 0;
}


/*
printf("[%s] %u %#010x\n", av[*ac_index], *opts, *opts);
printf("+%c+ %u %#010x\n", av[*ac_index][i], *opts, *opts);
printf("[%c] %d %d\n", av[*ac_index][i], i, j);
*/

/*
if (g_opts[j].id == str[i] && g_opts[j].str != NULL)
			{
				if (strncmp(g_opts[j].str, str + i, strlen(g_opts[j].str)) == 0)
				{
					opts &= ~g_opts[j].off;
					opts |= g_opts[j].on;
					break ;
				}
				else
					continue ;
			}
			if (g_opts[j].id == str[i])
			{
				opts &= ~g_opts[j].off;
				opts |= g_opts[j].on;
				break ;
			}
*/