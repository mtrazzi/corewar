#include "vm.h"

# define STR_ERROR_CYCLE "could not complete cycle"
# define DEBUG_RUN_VM   0
# define DEBUG_CHECK_LIVE 0

static void    ft_wait(void) //just to print step by step
{
    char *line = NULL;
    char *rem = NULL;
    while (!line || ft_strcmp(line, "s"))
        get_next_line(0, &line, &rem);
}

static void    check_lives(t_env *e)
{
    if (DEBUG_CHECK_LIVE)
        ft_printf("nb_checks : %d\nnb_live : %d\ne->cyc : %d\n", \
        e->nb_checks, e->nb_live, e->cyc);
    e->cyc_counter = 0;
    if (e->nb_live >= NBR_LIVE)
    {
		e->nb_live = 0;
        e->nb_checks = 0;
        e->cyc -= CYCLE_DELTA;
    }
    else if (e->nb_checks == MAX_CHECKS - 1)
    {
        e->nb_checks = 0;
        e->cyc -= CYCLE_DELTA;
    }
    else
        e->nb_checks += 1;
}

static int		del_not_live(t_prc **prc)
{
    if (!((*prc)->live))
    {
        if (*prc)
        {
            free(*prc);
            *prc = NULL;
        }
    }
    else
       (*prc)->live = 0;
	return (1);
}

int     run_vm(t_env *e)
{
    while (e->cyc > 0)
    {
        if (DEBUG_RUN_VM)
            ft_printf("e->cyc_since_beg : %d\ne->cyc : %d\ncounter : %d\n", \
            e->cyc_since_beg, e->cyc, e->cyc_counter);
        if (e->par.print)
            print_map(*e);
        if (do_one_cycle(e) < 0)
            return (ft_error_vm(STR_ERROR_CYCLE));
        e->cyc_counter += 1;
        if (e->cyc_counter == e->cyc)
        {
            check_lives(e);//if check_lives < 0 break ;
            dll_foreach_tmp(e->prc_lst, &del_not_live);
        }
        e->cyc_since_beg += 1;
        if (e->par.print && (e->cyc_since_beg % 5) == 1)
            ft_wait();
        if (e->par.print)
            clear_screen();
    }
    return (0);
}
