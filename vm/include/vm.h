#ifndef VM_H
# define VM_H

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include "dll.h"
# include "op.h"
# include <sys/types.h>
# include <stdio.h>
# include <limits.h>
# include <fcntl.h>

# define MAX_COLOR 4
# define NB_OP	   16

typedef struct		s_prc t_prc;
typedef struct		s_par t_par;
typedef struct		s_env t_env;
typedef struct		s_chp t_chp;
typedef struct		s_op  t_op;
typedef	int			t_do_op(t_env *e, t_prc *prc);

struct				s_prc
{
	u_int			pc;
	int				r[REG_NUMBER];	//registers
	int				carry;
	int				live;
	int				live_nb;
	int				id;
	int				cyc_left;
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
	int				dump;			//is ther a dump ?
	u_int			nb_cyc;			//nb_cyc befor dump
	u_int			nb_chp;			//how many .cor files
	t_chp			champions[MAX_PLAYERS];
};

struct				s_env
{
	u_char			map[MEM_SIZE];
	u_char			map_color[MEM_SIZE];
	t_dll			*prc_lst;
	int				cyc;			//cycles to die
	int				cyc_counter;	//counter of cycles (btw 0 and e->cyc)
	int				nb_checks;
	int				nb_live;		//nb of live since last check
	t_par			par;
};

/*
** ENV UTILS
*/

int		ft_init_vm(t_env *e);
int		ft_free_vm_env(t_env *e);
int		ft_error_vm(char *err_msg);
int		ft_perror_vm(void);

/*
** PARSING OF THE ARGUMENTS
*/

int		parse_arg_vm(int ac, char **av, t_env *e);

/*
** STRING UTILS
*/

int		ft_is_number(char *str);
int		ft_is_int(char *str);
u_int	convert_uint(u_int n);
u_int   convert_4_bytes(u_char b0, u_char b1, u_char b2, u_char b3);
u_int   convert_2_bytes(u_char b0, u_char b1);

/*
** PRINTING
*/

void	print_env(t_env e);
void	print_map(t_env e);
void	color_tab(void);
char	*g_color_tab[MAX_COLOR * 2 + 2];
int		print_prc(t_prc *prc);
void	clear_screen(void);

/*
** PREPARATION / CHAMPION PARSING
*/

int		parse_all_files(t_env *e);
int     init_all_processes(t_env *e);

/*
** FUNCTIONS FOR CYCLE HANDLING / CALLING PROCESSES
*/

int     run_vm(t_env *e);
int		do_one_cycle(t_env *e);
int		do_process(t_env *e, t_prc *prc); //must also change color of processes

/*
** IMPLEMENTATION OF OPERATIONS
*/

t_do_op *g_op_fun_tab[NB_OP + 1];
void	op_fun_tab_init(void)	;
int     live(t_env *e, t_prc *prc);
int     ld(t_env *e, t_prc *prc);
int     st(t_env *e, t_prc *prc);
int     add(t_env *e, t_prc *prc);
int     sub(t_env *e, t_prc *prc);
int     and(t_env *e, t_prc *prc);
int     or(t_env *e, t_prc *prc);
int     xor(t_env *e, t_prc *prc);
int     zjmp(t_env *e, t_prc *prc);
int     ldi(t_env *e, t_prc *prc);
int     sti(t_env *e, t_prc *prc);
int     ft_fork(t_env *e, t_prc *prc);
int     lld(t_env *e, t_prc *prc);
int     lldi(t_env *e, t_prc *prc);
int     lfork(t_env *e, t_prc *prc);
int     aff(t_env *e, t_prc *prc);


/*
** RESOURCES
*/

struct			s_op
{
	char	*name;
	u_int	nb_param;
	u_int	type_param[MAX_ARGS_NUMBER];//+1
	u_int	op_code;
	u_int	nb_cycles;
	char	*full_name;
	u_int	ocp;
	u_int	last_arg;
};

t_op	g_op_tab[NB_OP + 1];
void	op_tab_init(void);

/*
** TO DO
*/

//function to check if all number or players are different
//verbose mode
//write ("un processus dit que le joueur 3(rainbowdash) est en vie")

#endif
