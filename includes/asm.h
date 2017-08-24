#ifndef ASM_H

# define ASM_H
# include "libft.h"
# include "dll.h"

typedef struct		s_asm
{
	t_dll			*lst;
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

#endif
