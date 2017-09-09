#include <stdio.h>
#include "opts.h"

# define OPTS_D 0x00000001
# define OPTS_M 0x00000002
# define OPTS_V 0x00000004

t_opts g_opts[] = 
{
	{'d', "dump", 1, {{0, NULL}}, 1, 0},//init all null ?
	{'d', "debris", 3, {{0, NULL}, {0, NULL}, {0, NULL}}, 2, 0},
	{'a', NULL, 0, {}, 4, 0},
	{'b', NULL, 0, {}, 8, 0},
	{'c', NULL, 0, {}, 16, 0},
	{0, 0, 0, {0}, 0, 0}
};


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
	printf("i%d\n", i);
	if (i < 0)
		return (-1);
	printf("%d %#010x\n", opts, opts);
	return 0;
}