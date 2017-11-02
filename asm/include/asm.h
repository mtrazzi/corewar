/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 15:47:53 by pkirsch           #+#    #+#             */
/*   Updated: 2017/09/29 18:17:36 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include "dll.h"
# include "op.h"
# include <sys/types.h>

# if IND_SIZE != 2 ||  REG_SIZE != 4 || DIR_SIZE != REG_SIZE
#  error USER DEFINED ERROR: Bad value in op.h
# endif

# if REG_CODE != 1 || DIR_CODE != 2 || IND_CODE != 3
#  error USER DEFINED ERROR: Bad value in op.h
# endif

/*
** MAX_ARGS_NUMBER can't be sup signed INT_MAX
*/

# if MAX_ARGS_NUMBER != 4 || (REG_NUMBER < 1 || REG_NUMBER > 2147483647)
#  error USER DEFINED ERROR: Bad value in op.h
# endif

# define LABEL_NO			0
# define LABEL_2			2
# define LABEL_4			4

# define LIVE				0x0001
# define LD					0x0002
# define ST					0x0004
# define ADD				0x0008
# define SUB				0x0010
# define AND				0x0020
# define OR					0x0040
# define XOR				0x0080
# define ZJMP				0x0100
# define LDI				0x0200
# define STI				0x0400
# define FORK				0x0800
# define LLD				0x1000
# define LLDI				0x2000
# define LFORK				0x4000
# define AFF				0x8000

# define IS_LABEL_NO		0b1000000000011100
# define IS_LABEL_2			0b0110111100000000
# define IS_LABEL_4			0b0001000011100011
# define IS_PCB				0b1011011011111110

# define PAR_SIZE_REG		1
# define PAR_SIZE_IND		2

# define MAL_ERR			-40
# define ME					(MAL_ERR)

# define GNL_ERR			-100
# define IS_NOT_LABEL		-10
# define IS_LABEL_ONLY		11
# define IS_MORE_THAN_LABEL	12

# define BAD_OP_NAME		-20
# define BAD_OP_PARAM		-21

# define NAME_DIFFERENT		0
# define NAME_EQUAL			1

# define MAX_OP				17

typedef struct s_op		t_op;
typedef struct s_asm	t_asm;
typedef struct s_param	t_param;
typedef struct s_ope	t_ope;
typedef struct s_sym	t_sym;
typedef	struct s_parse	t_parse;

struct			s_asm
{
	t_dll		*to_skip_syms;
	t_dll		*syms;
	t_dll		*ops;
	t_header	header;
	int			fd;
};

/*
**	line is 0-indexed
**	c_ope = corresponding ope in g_op_tab
*/

struct			s_sym
{
	u_int		line_number_parsing_help;
	t_ope		*c_ope;
	u_int		sym;
	char		*label;
};

/*
**	ais = address in size
*/

struct			s_ope
{
	u_int		nb_param;
	u_int		type_param[MAX_ARGS_NUMBER];
	u_int		params[MAX_ARGS_NUMBER];
	u_int		op_code;
	u_int		size;
	u_int		ais;
	u_char		ocp;
	t_op		*op_tab_x;
	u_int		line_nb;
};

struct			s_op
{
	char		*name;
	u_int		nb_param;
	u_int		type_param[MAX_ARGS_NUMBER];
	u_int		op_code;
	u_int		nb_cycles;
	char		*full_name;
	u_int		ocp;
	u_int		label_size;
};

/*
**	alc = address line current
*/

struct			s_parse
{
	t_dll		*sym_curr;
	t_dll		*to_skip_curr;
	u_int		line_count;
	char		*add_line_start;
	char		*alc;
};

t_op			g_op_tab[MAX_OP];

/*
**	asm_parsing
*/

int				parsing(t_asm *a);
int				get_labels(t_asm *a);
int				get_header(t_asm *a, char **rem, t_parse *p);
void			init_t_parse(t_parse *p, t_asm *a);
char			*get_next_separator(char *str);
int				is_com(char *str);
int				ft_atoi_mod(const char *str);
int				free_str(char **str);

/*
**	parse_op
*/

int				check_params(char **str, t_op *ref, t_ope *ope, t_asm *a);
int				get_dir(char **str, int param_nb, t_ope *ope);
int				get_lab(char **str, int param_nb, t_ope *ope, t_dll *syms);
int				get_ind(char **str, int param_nb, t_ope *ope);
int				get_reg(char **str, int param_nb, t_ope *ope);

/*
**	creates
*/

t_dll			*create_ope_dll(t_ope *ope, t_op *ref);
t_dll			*create_add_label(char *str, int len, t_dll **syms,
									u_int symbol);

/*
**	syms
*/

t_sym			*does_label_exist_in_sym_dll(char *str, int len, t_dll *syms);
int				get_sym_by_sym(t_dll *dll, void *data);
u_int			get_next_symbol(t_dll *syms);

/*
**	op
*/

t_op			*does_op_exist_in_op_tab(char *str, int len);

/*
**	del
*/

void			del_sym(t_sym **sym);
int				clear_asm(t_asm *a);

/*
**	endian
*/

void			ft_print_hexa(u_int n);
void			write_be(int fd, u_int n, u_int size);

/*
**	error
*/

int				reopen_error(char *file_name);
int				error_parse(t_parse *p);

/*
**	file_handling
*/

int				update_fd_asm(t_asm *a, char *file_name);
int				open_file(char *file_name, int *fd);

/*
**	prep
*/

int				prep(t_asm *a);

/*
**	print
*/

void			print_header(t_asm *a);
void			print_cmds(t_asm *a);

/*
**	size
*/

int				nb_bytes_op(t_ope *ope);
int				calc_add_size(t_dll *dll);

/*
**	str_utils
*/

void			skip_whitespaces(char **str);
void			skip_to_whitespaces(char **str);
char			*get_next_whitespace(char *str);
void			skip_to(char **str, char c);
char			*get_next(char *str, char c);

#endif
