#ifndef ASM_H

# define ASM_H

# include "ft_printf.h"	
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

#define GNL_ERR -100
#define IS_NOT_LABEL -10
#define IS_LABEL_ONLY 11
#define IS_MORE_THAN_LABEL 12


#define BAD_OP_NAME -20//BAD_OP_CODE
# define BAD_OP_PARAM -21


#define NAME_DIFFERENT 0
#define NAME_EQUAL 1

typedef struct s_op		t_op;
typedef struct s_asm	t_asm;
typedef struct s_param	t_param;
typedef struct s_ope	t_ope;
typedef struct s_sym	t_sym;

struct			s_asm
{
	t_dll		*to_skip_syms;
	t_dll		*syms;
	t_dll		*ops;		//liste de lignes du .s
	header_t	header;	//header au debut du .cor || convert not a pointeur !
	int			fd;			//file descriptor du .cor
	//program size
};

//lire plusieurs fois le fichier to get les label et ainsi reperer les erreurs de %:label
//dans les ops des le parsing!
struct s_sym
{
	u_int	line_number_parsing_help;//0-indexed!
	t_ope	*corresponding_ope;
	u_int	sym;
	char	*label;
};

// struct			s_param
// {
// 	t_arg_type	type;
// 	u_int		n;
// 	u_int		sym;
// };

// struct			s_ope
// {
// 	u_int		sym;//char *label
// 	u_int		op_code;
// 	u_int		nb_par;
// 	t_param		p1;
// 	t_param		p2;
// 	t_param		p3;
// 	u_int		size;
// 	//t_op			*op_tab_x;
// };

struct			s_ope
{
	u_int	nb_param;
	u_int	type_param[MAX_ARGS_NUMBER];
	u_int	params[MAX_ARGS_NUMBER];
	u_int	op_code;
	u_int	size;
	u_int	address_in_size;//sum of precedent sizes
	u_char	ocp;
	t_op	*op_tab_x;
	u_int	line_nb;
};

// struct			s_sym
// {
// 	char		*label;
// 	u_int		sym;
// 	char		true_sym;
// };

struct			s_op
{
	char	*name;
	u_int	nb_param;
	u_int	type_param[MAX_ARGS_NUMBER];//+1
	u_int	op_code;
	u_int	nb_cycles;
	char	*full_name;
	u_int	ocp;
	u_int	label_size;
};

typedef	struct s_parse	t_parse;
struct			s_parse
{
	t_dll		*sym_curr;
	t_dll		*to_skip_curr;
	u_int		line_count;
	char		*add_line_start;
	char		*alc;//*add_line_curr;
};

#define MAX_OP 17
t_op    g_op_tab[MAX_OP];

int		ft_is_withespace(char c);
char	*get_next_whitespace(char *str);
char	*get_next_separator(char *str);
void	skip_to_whitespaces(char **str);
void	skip_whitespaces(char **str);
void	skip_to(char **str, char c);
int		ft_atoi(const char *str);
int		ft_atoi_mod(const char *str);
int		ft_isdigit(char c);
char	*get_next(char *str, char c);


int		init_g_op(void);

t_ope	*create_ope(void);
t_sym	*create_sym(char *label, u_int symbol);
t_sym	*does_label_exist_in_sym_dll(char *str, int len, t_dll *syms);
int		create_add_label(char *str, int len, t_dll **syms, u_int symbol);
t_dll	*create_ope_dll(t_ope *ope, t_op *ref);
t_op	*does_op_exist_in_op_tab(char *str, int len);


int		is_com(char *str);
int		get_labels(t_asm *a);
int		parsing(t_asm *a);
int		get_header(t_asm *a, char **rem, t_parse *p);
int		check_params(char **str, t_op *ref, t_ope *ope, t_asm *a);

int		prep(t_asm *a);

int		get_dir(char **str, int param_nb, t_ope *ope);//IDX_MOD
int		get_lab(char **str, int param_nb, t_ope *ope, t_dll *syms);//int type
int		get_ind(char **str, int param_nb, t_ope *ope);//MOD_QQCHOSE
int		get_reg(char **str, int param_nb, t_ope *ope);

int		error_parse(t_parse *p);

//move in DLLST
void	dll_print_f(char *msg, t_dll *lst, void f());

void	ope_str_(t_ope *ope);
void	sym_dll_print(char *msg, t_dll *lst);
void	sym_str_(t_sym *sym);

u_char	calculate_pcb(t_ope *ope);
int		nb_bytes_op(t_ope *ope);
int		calc_add_size(t_dll *dll);
int		get_sym_by_sym(t_dll *dll, void *data);

int		update_fd_asm(t_asm *a, char *file_name);
void	print_header(t_asm *a);
void	write_be(int fd, int n, u_int size);//CHANGE INT?
void	print_cmds(t_asm *a);

#endif








