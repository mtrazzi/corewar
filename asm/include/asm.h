#ifndef ASM_H

# define ASM_H

# include "get_next_line.h"
# include "libft.h"
# include "dll.h"
# include "op.h"
# include <sys/types.h>

# define LABEL_NO	0
# define LABEL_2	2
# define LABEL_4	4

#define LIVE		0x0001
#define LD			0x0002
#define ST	 		0x0004
#define	ADD 		0x0008
#define SUB 		0x0010
#define AND 		0x0020
#define OR			0x0040
#define XOR			0x0080
#define ZJMP 		0x0100
#define LDI			0x0200
#define STI			0x0400
#define FORK		0x0800
#define LLD			0x1000
#define LLDI		0x2000
#define LFORK		0x4000
#define AFF			0x8000

#define IS_LABEL_NO 0b1000000000011100	
#define	IS_LABEL_2	0b0110111100000000	
#define	IS_LABEL_4	0b0001000011100011	
#define IS_PCB		0b1011011011111110	

# define PAR_SIZE_REG 1
# define PAR_SIZE_IND 2

# define MAL_ERR -40

typedef struct s_op		t_op;
typedef struct s_asm	t_asm;
typedef struct s_param	t_param;
typedef struct s_ope	t_ope;
typedef struct s_sym	t_sym;

struct			s_asm
{
	t_dll		*syms;
	t_dll		*ops;		//liste de lignes du .s
	header_t	*header;	//header au debut du .cor
	int			fd;			//file descriptor du .cor
};

struct			s_param
{
	t_arg_type	type;
	u_int		n;
	u_int		sym;
};

struct			s_ope
{
	u_int		sym;//char *label
	u_int		op_code;
	u_int		nb_par;
	t_param		p1;
	t_param		p2;
	t_param		p3;
	u_int		size;
	//t_op			*op_tab_x;
};

struct			s_sym
{
	char		*label;
	u_int		sym;
	char		true_sym;
};

struct			s_op
{
	char	*name;
	u_int	nb_param;
	u_int	type_param[MAX_ARGS_NUMBER + 1];
	u_int	op_code;
	u_int	nb_cycles;
	char	*full_name;
	u_int	ocp;
	u_int	last_arg;
};

struct			s_typparam
{
	
};

#define MAX_OP 17

int		ft_is_withespace(char c);
char	*get_next_whitespace(char *str);
char	*get_next_separator(char *str);
void	skip_to_whitespaces(char **str);
void	skip_whitespaces(char **str);

t_sym	*create_sym(char *label, u_int symbol);

t_sym	*does_label_exist_in_sym_dll(char *str, int len, t_dll *syms);
int		create_add_label(char *str, int len, t_dll **syms, u_int symbol);

t_op	*does_op_exist_in_op_tab(char *str, int len);

#endif
