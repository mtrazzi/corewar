/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 16:31:10 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/09/10 16:31:28 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

# define V_0 0
# define V_1 1
# define V_2 2
# define V_4 4
# define V_8 8
# define V_16 16

# define LAST_TWO_BITS 0b00000011

# define STR_ERR_MALLOC_PRC "cannot malloc process"
# define STR_ERR_MACRO "values in header have changed : undefined behavior"
# define STR_ERROR_CYCLE "could not complete cycle"

typedef struct s_prc	t_prc;
typedef struct s_par	t_par;
typedef struct s_color	t_color;
typedef struct s_env	t_env;
typedef struct s_chp	t_chp;
typedef struct s_op	t_op;
typedef	int			t_do_op(t_env *e, t_prc *prc);

struct				s_op
{
	char			*name;
	u_int			nb_param;
	u_int			type_param[MAX_ARGS_NUMBER];
	u_int			op_code;
	u_int			nb_cycles;
	char			*full_name;
	u_int			ocp;
	u_int			last_arg;
};

struct				s_prc
{
	u_int			pc;
	int				r[REG_NUMBER + 1];
	int				carry;
	int				live;
	int				live_nb;
	int				id;
	int				cyc_left;
	int				op_code;
	int				cyc_last_live;
};

struct				s_chp
{
	int				nb; //numero du champion
	u_int			magic;
	u_int			prog_size;
	char			name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
	char			*file_name;
};

struct				s_par
{
	int				verb;
	int				print;
	int				dump;
	int				nb_cyc;
	u_int			nb_chp;
	t_chp			champions[MAX_PLAYERS];
};

struct				s_color
{
	int				color;
	int				highlight_count;
};

struct				s_env
{
	u_char			map[MEM_SIZE];
	t_color			map_color[MEM_SIZE];
	t_dll			*prc_lst;
	int				cyc;
	int				cyc_counter;
	int				nb_checks;
	int				nb_live;
	t_par			par;
	int				cyc_since_beg;
	int				last_alive;
	int				last_id;
	int				spd;
};

/*
** ENV UTILS
*/

int					ft_init_vm(t_env *e);
int					ft_free_vm_env(t_env *e);
int					ft_error_vm(char *err_msg);
int					ft_perror_vm(void);

/*
** PARSING OF THE ARGUMENTS
*/

int					parse_arg_vm(int ac, char **av, t_env *e);

/*
** STRING UTILS
*/

int					ft_is_number(char *str);
int					ft_is_int(char *str);
u_int				convert_uint(u_int n);
int					convert_4_bytes(u_char b0, u_char b1, u_char b2, u_char b3);
short				convert_2_bytes(u_char b0, u_char b1);

/*
** PRINTING
*/

void				print_env(t_env e);
void				print_map(t_env e);
void				color_tab(void);
char				*g_color_tab[MAX_COLOR * 2 + 2];
int					print_prc(t_prc *prc);
void				clear_screen(void);
void				print_introduction(t_env *e);
void				print_conclusion(t_env *e);
void				print_adv(t_env *e, int pos, int skip);
int					dump(t_env *e);

/*
** PREPARATION / CHAMPION PARSING
*/

int					parse_all_files(t_env *e);
int					init_all_processes(t_env *e);

/*
** FUNCTIONS FOR CYCLE HANDLING / CALLING PROCESSES
*/

int					run_vm(t_env *e);
int					do_one_cycle(t_env *e);
int					do_process(t_env *e, t_prc *prc);
int					are_macro_correct(void);
int					process_load_op(t_env *e, t_prc *prc);
int					process_exec_op_update_cyc_left(t_env *e, t_prc *prc);
int					check_params(t_env *e, t_prc *prc, int op_code);
void				check_lives(t_env *e);
void				del_and_update(t_env *e, t_dll **begin_lst, int all);

/*
** PARSING FOR OPERATIONS
*/

int					nb_bytes_to_skip(u_char op_code, u_char ocp);
int					sizeof_param(u_char op_code, u_char type_of_param);
int					get_value(t_env *e, u_char type_of_param, t_prc *prc,
					u_int pos);
int					lget_value(t_env *e, u_char type_of_param, t_prc *prc,
					u_int pos);
int					get_index(t_env *e, u_char type_of_param, t_prc *prc,
					u_int pos);

/*
** IMPLEMENTATION OF OPERATIONS
*/

t_do_op				*g_op_fun_tab[NB_OP + 1];
void				op_fun_tab_init(void);
int					live(t_env *e, t_prc *prc);
int					ld(t_env *e, t_prc *prc);
int					st(t_env *e, t_prc *prc);
int					add(t_env *e, t_prc *prc);
int					sub(t_env *e, t_prc *prc);
int					and(t_env *e, t_prc *prc);
int					or(t_env *e, t_prc *prc);
int					xor(t_env *e, t_prc *prc);
int					zjmp(t_env *e, t_prc *prc);
int					ldi(t_env *e, t_prc *prc);
int					sti(t_env *e, t_prc *prc);
int					ft_fork(t_env *e, t_prc *prc);
int					lld(t_env *e, t_prc *prc);
int					lldi(t_env *e, t_prc *prc);
int					lfork(t_env *e, t_prc *prc);
int					aff(t_env *e, t_prc *prc);
int					mul(t_env *e, t_prc *prc);
int					death(t_env *e, t_prc *prc);
int					nand(t_env *e, t_prc *prc);
int					jump(t_env *e, t_prc *prc);
int					bomb(t_env *e, t_prc *prc);
int					copy(t_env *e, t_prc *prc);

/*
** OP UTILS
*/

int					is_real_number(t_env *e, int nb);
void				copy_value(int value, t_env *e, u_int pos, u_char color);
t_prc				*new_prc(u_int pc, int nb, int id);
u_int				mod_map(int nbr);
int					get_color(t_env *e, int nb);

/*
** RESOURCES
*/

t_op				g_op_tab[NB_OP + 1];
void				op_tab_init(void);

#endif
