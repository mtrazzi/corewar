#ifndef ASM_H

# define ASM_H
# include "libft.h"

/*
** Structure for list of strings 
** for the parsing of the .s file
*/

typedef struct		s_op
{
	struct s_op		*next;
	char			*op;
}					t_op;

/*
** Structure for the environment 
** for the assembler
*/

typedef struct		s_asm
{
	t_op			*lst_op;
}					t_asm;

/*
** Functions for list of strings
*/

void	ft_add_to_end(char *op, t_op **lst);
char	*ft_pop_op(t_op **lst);
void	ft_print_lst_op(t_op *t);
void	ft_free_lst_op(t_op *lst);

/*
** Functions that deal with the 
** asm environment
*/

t_asm	*ft_init_asm(void);
void	ft_free_asm_env(t_asm *e);

#endif
