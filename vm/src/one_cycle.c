#include "vm.h"

# define STR_ERROR_PROCESS "error in handling a process"

# define DEBUG_ONE_CYCLE 0

int     do_one_cycle(t_env *e)
{
    t_dll *elt;

    elt = e->prc_lst;
    if (DEBUG_ONE_CYCLE)
        dll_foreach_content(e->prc_lst, print_prc);
    while (elt && (((t_prc *)(elt->content))->newly_created) == 0)
    {
        // ft_printf("{yellow}%d {green}%p %d{eoc} ", e->cyc_since_beg, ((t_prc *)elt->content), ((t_prc *)elt->content)->pc);
        if (process_exec_op_update_cyc_left(e, elt->content) < 0)
            return (ft_error_vm(STR_ERROR_PROCESS));
        // ft_printf("{green}%d{eoc}\n", ((t_prc *)elt->content)->pc);
        elt = elt->next;
    }
    elt = e->prc_lst;
    while (elt)
    {
        // ft_printf("{yellow}%d {cyan}%p %d{eoc} ", e->cyc_since_beg, ((t_prc *)elt->content), ((t_prc *)elt->content)->pc);
        if (process_load_op(e, elt->content) < 0)
            return (ft_error_vm(STR_ERROR_PROCESS));
        // ft_printf("{cyan}%d{eoc}\n", ((t_prc *)elt->content)->pc);
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
