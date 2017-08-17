#include "asm.h"

void	ft_add_to_end_lst(t_list **lst, void const *content)
{
    t_list *tmp;
 
    if (!(*lst))
    {
        *lst = ft_lstnew(content);
        return ;
    }
    tmp = *lst;
    while ((*lst)->next)
        *lst = (*lst)->next;
    (*lst)->next = ft_lstnew(content);
    *lst = tmp;
}

void	*ft_pop_lst(t_list **lst)
{
    void	*s;
    t_list	*tmp;

	if (!(*lst))
		return (NULL);
	s = NULL;
	ft_memcpy(s, (*lst)->content, sizeof((*lst)->content));
    tmp = *lst;
    *lst = (*lst)->next;
    ft_memdel((void **)&tmp->content);
    ft_memdel((void **)&tmp);
    return (s);
}
