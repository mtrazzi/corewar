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

struct				s_prc			//process
{
	u_int			pc;
	int				r[REG_NUMBER + 1];	//registers r1, ..., r16 == r[1], ..., r[16]
	int				carry;
	int				live;
	int				live_nb;		//nb of the champion from live
	int				id;				//nb of the pc
	int				cyc_left;		//cycles left before operation
	int				op_code;
	int				newly_created;
	// int				op_done;
};

struct				s_chp			//champion
{
	int				nb;
	u_int			magic;
	u_int			prog_size;
	char			name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
	char			*file_name;
};

struct				s_par			//parameters (from parsing)
{
	int				verb;			//verbose option : show operations
	int				print;			//print the map every 5 cycles
	int				dump;			//is there a dump ?
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
	t_par			par;			//parameters given after parsing of args
	int				cyc_since_beg;  //nb of cycles since beginning
	int				last_alive;		//nb of last live done
	int				last_id;
	int				speed;
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
int		convert_4_bytes(u_char b0, u_char b1, u_char b2, u_char b3);
short	convert_2_bytes(u_char b0, u_char b1);

/*
** PRINTING
*/

void	print_env(t_env e);
void	print_map(t_env e);
void	color_tab(void);
char	*g_color_tab[MAX_COLOR * 2 + 2];
int		print_prc(t_prc *prc);
void	clear_screen(void);
void	print_introduction(t_env *e);
void	print_conclusion(t_env *e);
void	print_ADV(t_env *e, int pos, int skip);

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

int		process_load_op(t_env *e, t_prc *prc);
int		process_exec_op_update_cyc_left(t_env *e, t_prc *prc);

/*
** PARSING FOR OPERATIONS
*/

int     nb_bytes_to_skip(u_char op_code, u_char ocp);
int     sizeof_param(u_char op_code, u_char type_of_param);
int     get_value(t_env *e, u_char type_of_param, t_prc *prc, u_int pos);
short	get_index(t_env *e, u_char type_of_param, t_prc *prc, u_int pos);

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
** OP UTILS
*/

int     is_real_number(t_env *e, int nb);
void	copy_value(int value, t_env *e, u_int pos);
t_prc	*new_prc(u_int pc, int nb, int id);

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

//dump memory with option -d
//function to check if all number or players are different
//change usage
//uncompability of certain options (-d and -m for example)
//color significant bytes while performing operations

//with pkirsch

//flags in t_par instead of multiple int
//change usage
//make options incompatible (-v and -m)
//condition to go out of loop run_vm

/*
** BONUS
*/

//use realloc and lseek
//pointer to t_chp in prc to visualize in ncurse

#endif
