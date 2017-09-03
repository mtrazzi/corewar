#include "vm.h"

# define STR_ERROR_PROCESS "error in handling a process"

# define DEBUG_ONE_CYCLE 0

int     do_one_cycle(t_env *e)
{
    t_dll *elt;

    elt = e->prc_lst;
    if (DEBUG_ONE_CYCLE)
        dll_foreach_content(e->prc_lst, print_prc);
    while (elt && e->cyc_since_beg != 0)
    {
        if (process_exec_op_update_cyc_left(e, elt->content) < 0)
            return (ft_error_vm(STR_ERROR_PROCESS));
        elt = elt->next;
    }
    elt = e->prc_lst;
    while (elt)
    {
        if (process_load_op(e, elt->content) < 0)
            return (ft_error_vm(STR_ERROR_PROCESS));
        elt = elt->next;
    }
    return (0);
}

/*int     do_one_cycle(t_env *e)
{
    t_dll *elt;

    elt = e->prc_lst;
    if (DEBUG_ONE_CYCLE)
        dll_foreach_content(e->prc_lst, print_prc);
    while (elt)
    {
        if (do_process(e, elt->content) < 0)
            return (ft_error_vm(STR_ERROR_PROCESS));
        elt = elt->next;
    }
    elt = e->prc_lst;
    while (elf)
    {

    }
    return (0);
}*/
