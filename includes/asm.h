#ifndef ASM_H

# define ASM_H
# include "libft.h"
# include "dll.h"
# include "op.h"
# include <sys/types.h>

typedef struct		s_asm
{
	t_dll			*lst;		//liste de lignes du .s
	header_t		header;		//header au debut du .cor
	int				fd;			//file descriptor du .cor
}					t_asm;

/*
** ENVIRONMENT 
*/

t_asm				*ft_init_asm(void);
void				ft_free_asm_env(t_asm *e);

/*
** PARSING
*/

void				ft_file_to_lst_asm(t_asm *e, char *file_name);

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
