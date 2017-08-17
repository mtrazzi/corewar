#ifndef ASM_H

# define ASM_H
# include "libft.h"

/*
** Structure for the environment 
** for the assembler
*/

typedef struct		s_asm
{
	t_list			*lst;
}					t_asm;

/*
** Functions for lists 
*/

void				ft_add_to_end_lst(t_list **lst, void const *content);
void				*ft_pop_lst(t_list **lst);
void				ft_print_lst_str(t_list *lst);

/*
** Functions that deal with the 
** asm environment
*/

t_asm				*ft_init_asm(void);
void				ft_free_asm_env(t_asm *e);

/*
** Functions for parsing
*/

void				ft_file_to_lst_asm(t_asm *e, char *file_name);

/*
** Functions for error handling
*/

void				ft_error_asm(t_asm *e, char *error_message);
void				ft_perror_asm(t_asm *e);

#endif
