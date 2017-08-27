#ifndef ASM_H

# define ASM_H
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

typedef struct		s_asm
{
	t_dll			*syms;
	t_dll			*ops;		//liste de lignes du .s
	header_t		*header;	//header au debut du .cor
	int				fd;			//file descriptor du .cor
}					t_asm;

typedef struct		s_param
{
	t_arg_type		type;
	u_int			n;
	u_int			sym;
}					t_param;

typedef	struct		s_ope
{
	char			*label;
	u_int			op_code;
	u_int			nb_par;
	t_param			p1;
	t_param			p2;
	t_param			p3;
	u_int			size;
}					t_ope;

typedef	struct		s_sym
{
	char			*symbol;
	u_int			nb;
}					t_sym;

/*
** ENVIRONMENT 
*/

int					ft_init_asm(t_asm *e);
void				ft_free_asm_env(t_asm *e);

/*
** PARSING FILE
*/

int					ft_file_to_lst_asm(t_asm *e, char *file_name);
char				*ft_process_line(char *line);
t_arg_type			ft_give_type(char *param);

/*
** ERROR
*/

int					ft_error_asm(t_asm *e, char *error_message);
int					ft_perror_asm(t_asm *e);


/*
** PRINTING
*/

void				ft_print_lst_str(t_dll *lst);
void				ft_print_hexa(u_int n);


/*
** I/O
*/

int					ft_update_fd_asm(t_asm *e, char *file_name);
u_int				ft_convert_endian(u_int n);
void				ft_write_be(int fd, u_int n, u_int size);
void				ft_write_header(int fd, header_t t);
void				ft_write_op(int fd, t_ope op);

/*
** PROCESSING
*/

int					nb_bytes_op(t_ope op);
t_arg_type			ft_give_pcb(t_ope op);
int					give_label(u_int op_code);

#endif
