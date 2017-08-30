#include "vm.h"

# define STR_ERROR_CYCLE "could not complete cycle"

static void    check_lives(t_env *e)
{
    e->cyc_counter = 0;
    if (e->nb_live >= NBR_LIVE)
        e->cyc -= CYCLE_DELTA;
    else if (e->nb_checks == MAX_CHECKS - 1)
    {
        e->nb_checks = 0;
        e->cyc -= CYCLE_DELTA;
    }
    else
        e->nb_checks += 1;
}

static void     del_not_live(t_prc *prc)
{
    if (!prc->live)
        free(prc);
    else
        prc->live = 0;
}

int     run_vm(t_env *e)
{
    while (e->cyc > 0)
    {
        if (do_one_cycle(e) < 0)
            return (ft_error_vm(STR_ERROR_CYCLE));
        e->cyc_counter += 1;
        if (e->cyc_counter == e->cyc)
        {
            check_lives(e);
            dll_del_f(&e->prc_lst, &del_not_live);
        }
    }
    return (0);
}
