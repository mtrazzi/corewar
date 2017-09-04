#include "vm.h"

# define STR_ERROR_CYCLE "could not complete cycle"
# define DEBUG_RUN_VM   0
# define DEBUG_CHECK_LIVE 0

static void    ft_wait(t_env *e) //just to print step by step
{
    char *line = NULL;
    char *rem = NULL;
    while (!line || ft_strcmp(line, "s"))
	{
        get_next_line(0, &line, &rem);
		if (!ft_strcmp(line, "r"))
			e->speed += 5;
		else if (!ft_strcmp(line, "l"))
			e->speed -= 5;
		print_map(*e);
	}
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

//static int		del_not_live(t_prc **prc)
//{
//    if (!((*prc)->live))
//    {
//        if (*prc)
//        {
//			ft_printf("KILLED IT !!!\n");
//            free(*prc);
//            *prc = NULL;
//        }
//    }
//    else
//       (*prc)->live = 0;
//	return (1);
//}

static void		del_and_update(t_env *e, t_dll **begin_lst)
{
	t_dll *prc_lst;
	t_dll *next;
	t_dll *last_alive;
    t_prc *prc;

	prc_lst = *begin_lst;
	last_alive = NULL;
	while (prc_lst)
	{
		next = prc_lst->next;
        prc = (t_prc *)prc_lst->content;
		if (prc->live == 0)
        {
            if (e->par.verb & V_8)
                ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
                            prc->id, e->cyc_since_beg - prc->cyc_last_live, e->cyc);
			dll_delone(&prc_lst);
        }
		else if (!last_alive)
            last_alive = prc_lst;
        if (prc_lst)
            prc->live = 0;
		prc_lst = next;
	}
	*begin_lst = last_alive;
}

int     run_vm(t_env *e)
{
    while (e->cyc > 0 && e->prc_lst)
    {
        if (DEBUG_RUN_VM)
            ft_printf("e->cyc_since_beg : %d\ne->cyc : %d\ncounter : %d\n", \
            e->cyc_since_beg, e->cyc, e->cyc_counter);
        if (e->par.print && (e->cyc_since_beg % e->speed == 0))
            print_map(*e);
        if (do_one_cycle(e) < 0)
            return (ft_error_vm(STR_ERROR_CYCLE));
        e->cyc_counter += 1;
        e->cyc_since_beg += 1;
        if (e->par.verb & V_2)
            ft_printf("It is now cycle %d\n", e->cyc_since_beg);
        if (e->cyc_counter == e->cyc)
        {
            check_lives(e);//if check_lives < 0 break ;
            //dll_foreach_tmp(e->prc_lst, &del_not_live);
            del_and_update(e, &(e->prc_lst));
        }
        if (e->par.print && (e->cyc_since_beg % e->speed) == 1)
            ft_wait(e);
        if (e->par.print)
            clear_screen();
    }
    return (0);
}
