#include "asm.h"

t_op	*ft_new_op(char *op)
{
    t_op *t;
    
    t = ft_memalloc(sizeof(t_op));
    t->next = NULL;
    t->op = ft_strdup(op);
    return (t);
}

void	ft_add_to_end(char *op, t_op **lst)
{
    t_op *tmp;
    
    if (!(*lst))
    {
        *lst = ft_new_op(op);
        return ;
    }
    tmp = *lst;
    while ((*lst)->next != NULL)
        *lst = (*lst)->next;
    (*lst)->next = ft_new_op(op);
    *lst = tmp;
}

char	*ft_pop_op(t_op **lst)
{
    char *s;
    t_op *tmp;
    
    s = ft_strdup((*lst)->op);
    tmp = *lst;
    *lst = (*lst)->next;
    free(tmp->op);
    free(tmp);
    return (s);
}

void	ft_print_lst_op(t_op *t)
{
    while (t)
    {
        ft_putstr(t->op);
        ft_putchar('\n');
        t = t->next;
    }
}
