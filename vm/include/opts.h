#ifndef OPTS_H
# define OPTS_H

# include <stdlib.h>
# include <sys/types.h>

# define MAX_PARAMS 4

# define OPT_COLLISION "option collision"
# define OPT_REPEAT "option repeated to many times"
# define OPT_NOT "invalid option"
# define OPT_NOT_ENOUGH_PARAM "an option does not have enough param"
# define OPT_AFTER_ARG "options must appear before program arguments"

typedef struct s_opts		t_opts;
typedef struct s_opt_param	t_opt_param;

struct s_opt_param
{
	long	value;
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

int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);

int		ft_error(char *msg);

int		parse_params(int ac, char **av, u_int *opts);

#endif