#ifndef OPTS_H
# define OPTS_H

# include <stdlib.h>
# include <sys/types.h>
# include "libft.h"

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

#define FORMAT_LEN		10
#define	REST_NONE		0x00
#define REST_CONTAINS	0x01
#define REST_EQUAL		0x02
#define REST_END		0x04
typedef struct s_prog_param	t_prog_param;
struct s_prog_param
{
	char	*format;//format[FORMAT_LEN];
	u_int	mode;
	int		associated_opts_id;
	int		param_index;
};
/*
**	to implement:
**	
*/
//what if input == '.cor' should ne valid

extern t_opts g_opts[];
extern t_prog_param g_prog_param[];

int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);

int		ft_error(char *msg);

int		parse_params(int ac, char **av, u_int *opts);

int			is_empty_op(t_opts *opt);//

#endif
