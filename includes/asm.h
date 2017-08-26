#ifndef ASM_H

# define ASM_H
# include "libft.h"
# include "dll.h"
# include "op.h"
# include <sys/types.h>

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

t_asm				ft_init_asm(void);
void				ft_free_asm_env(t_asm *e);

/*
** PARSING
*/

int					ft_file_to_lst_asm(t_asm *e, char *file_name);
char				*ft_process_line(char *line);

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
void				ft_write_be(int fd, u_int n);
void				ft_write_header(int fd, header_t t);

#endif
