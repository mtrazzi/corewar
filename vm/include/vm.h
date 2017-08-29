#ifndef VM_H
# define VM_H

# include "libft.h"
# include "ft_printf.h"
# include "dll.h"
# include "op.h"
# include <sys/types.h>
# include <stdio.h>
# include <limits.h>
# include <fcntl.h>

# define ERR_PARSING_ARG -10
# define ERR_PARSING_OPT -11
# define ERR_PARSING_CHP -12
# define ERR_NB_CHP			 -13

# define ERR_OPEN_FILE   -20
# define ERR_CLOSE_FILE  -21
# define ERR_FORMAT_FILE -22
# define ERR_MAGIC			 -23

typedef struct		s_prc t_prc;
typedef struct		s_par t_par;
typedef struct		s_env t_env;
typedef struct		s_chp	t_chp;

struct				s_prc
{
	u_int			pc;
	int				r[REG_NUMBER];	//registers
	int				carry;
	int				live;
	int				id;
};

struct				s_chp
{
	int				nb;
	u_int			magic;
	u_int			prog_size;
	char			name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
	char			*file_name;
};

struct				s_par
{
	int				dump;
	int				nb_cyc;
	int				nb_chp;
	t_chp			champions[MAX_PLAYERS];
};

struct				s_env
{
	u_char			map[MEM_SIZE];
	t_dll			*prc_lst;
	int				cyc;			//cycles to die
	int				nb_live;		//nb of live since last check
	t_par			par;
};

/*
** ENV UTILS
*/

int		ft_init_vm(t_env *e);
int		ft_free_vm_env(t_env *e);
int		ft_error_vm(int err_nb, char *err_msg);
int		ft_perror_vm(int err_nb);

/*
** PARSING OF THE ARGUMENTS //VM must deal with -n and -dump options
*/

int		parse_arg_vm(int ac, char **av, t_env *e);

/*
** STRING UTILS
*/

int		ft_is_number(char *str);
int		ft_is_int(char *str);
u_int	convert_uint(u_int n);

/*
** PARSING OF .COR FILES
*/

int		parse_all_files(t_env *e);

/*
** PRINTING
*/

void	print_env(t_env e);

/*
** PREPARATION / CHAMPION PARSING
*/

//.cor files must be written in the vm memory with correct spacing
//at the beginning and all processes must be initialized

/*
** IMPLEMENTATION OF OPERATIONS
*/


#endif
