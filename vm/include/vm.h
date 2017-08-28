#ifndef VM_H

# define VM_H

# include "libft.h"
# include "ft_printf.h"
# include "dll.h"
# include "op.h"
# include <sys/types.h>
# include <stdio.h>
# define ERR_PARSING -10

typedef struct		s_prc t_prc;
typedef struct		s_par t_par;
typedef struct		s_env t_env;

struct				s_prc
{
	u_int			pc;
	int				r[REG_NUMBER];	//registers
	int				carry;
	int				live;
	int				id;
};

struct				s_par
{
	int				dump;
	int				nb_cyc;
	int				nb_files;
	char			*file_names[4];
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
void	ft_free_vm_env(t_env *e);
int		ft_error_vm(t_env *e, char *err_msg);
int		ft_perror_vm(t_env *e);

/*
** PARSING OF THE ARGUMENTS //VM must deal with -n and -dump options
*/

int		parse_arg_vm(int ac, char **av, t_env *e);

/*
** PARSING OF .COR FILES
*/

int		ft_parse_file(t_env *e, char *file_name);

/*
** PREPARATION / CHAMPION PARSING
*/

//.cor files must be written in the vm memory with correct spacing
//at the beginning and all processes must be initialized

/*
** IMPLEMENTATION OF OPERATIONS
*/


#endif
