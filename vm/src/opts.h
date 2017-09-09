#ifndef OPTS_H
# define OPTS_H

# include <stdlib.h>
# include <sys/types.h>
#include <string.h>//

# define MAX_PARAMS 4

typedef struct s_opts		t_opts;
typedef struct s_opt_param	t_opt_param;

struct s_opt_param
{
	long	value;//?
	char	*arg;
};

struct s_opts
{
	int				id;
	char			*str;
	int				nb_param;
	t_opt_param		params[MAX_PARAMS];
	u_int			on;
	u_int			off;
};

extern t_opts g_opts[];

int		parse_params(int ac, char **av, u_int *opts);

#endif