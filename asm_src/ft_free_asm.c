#include "asm.h"

void	ft_free_lst_op(t_op *lst)
{
	t_op *tmp;

	if (!lst)
		return ;
	while (lst->next)
	{
		tmp = lst->next;
		ft_strdel(&(lst->op));
		ft_memdel((void **)&lst);
		lst = tmp;
	}
	ft_strdel(&(lst->op));
	ft_memdel((void **)&lst);
}

void	ft_free_asm_env(t_asm *e)
{
	ft_free_lst_op(e->lst_op);
	ft_memdel((void **)&e);
}
