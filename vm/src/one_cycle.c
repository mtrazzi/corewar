#include "vm.h"

# define STR_ERROR_PROCESS "error in handling a process"

int     do_one_cycle(t_env *e)
{
    t_dll *elt;

    elt = e->prc_lst;
    while (elt)
    {
        if (do_process(e, elt->content) < 0)
            return (ft_error_vm(STR_ERROR_PROCESS));
        elt = elt->next;
    }
    return (0);
}