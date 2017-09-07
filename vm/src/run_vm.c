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
		else if (ft_is_int(line))
			e->speed = ft_atoi(line);
		print_map(*e);
	}
}

static void    check_lives(t_env *e)
{
	static u_int last_cyc_number = 0;

	// ft_printf("{cyan}SHAKE IT BABE (last check cycle #%d) (now%d) %d [%d]\n", last_cyc_number, e->cyc_since_beg, e->cyc_since_beg - last_cyc_number, CYCLE_DELTA);
	last_cyc_number = e->cyc_since_beg;
	// if (DEBUG_CHECK_LIVE)
	// 	ft_printf("nb_checks : %d\nnb_live : %d\ne->cyc : %d\n", \
	// 	e->nb_checks, e->nb_live, e->cyc);
	e->cyc_counter = 0;
	if (e->nb_live >= NBR_LIVE)
	{
		// ft_printf("{blue}BEFORE nb_live %d   nb_checks %d (ctd %d) %d{eoc}\n", e->nb_live, e->nb_checks, e->cyc, e->cyc_since_beg);
		e->nb_live = 0;
		e->nb_checks = 0;
		e->cyc -= CYCLE_DELTA;
		if (e->par.verb & V_2)
			ft_printf("Cycle to die is now %d\n", e->cyc);//u?
			// ft_printf("{blue}Cycle to die is now %d{eoc}\n", e->cyc);//u?
	}
	else if (e->nb_checks == MAX_CHECKS - 1)
	{
		// ft_printf("{green}CHECK TO zero from %d{eoc}\n", e->nb_checks);
		e->nb_checks = 0;
		e->nb_live = 0;
		e->cyc -= CYCLE_DELTA;
		if (e->par.verb & V_2)
			ft_printf("Cycle to die is now %d\n", e->cyc);//u?
			// ft_printf("{blue}Cycle to die is now %d{eoc}\n", e->cyc);//u?
	}
	else
	{
		// ft_printf("{red}INC CHECK from %d to %d{eoc}\n", e->nb_checks, e->nb_checks + 1);
		e->nb_checks += 1;
		e->nb_live = 0;
	}
}

static void		del_and_update(t_env *e, t_dll **begin_lst, int all)
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
		if (prc->live == 0 || all)
		{
			if (e->par.verb & V_8)
				ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
							prc->id, e->cyc_since_beg - prc->cyc_last_live, e->cyc);
			dll_delone(&prc_lst);
		}
		else if (!last_alive)
			last_alive = prc_lst;
		if (prc_lst)
		{
			prc->live = 0;
			prc->live_nb = 0;
		}
		prc_lst = next;
	}
	*begin_lst = last_alive;
}

int     run_vm(t_env *e)
{
	while (e->prc_lst)
	{
		if (e->cyc_counter == (e->cyc < 0 ? -e->cyc : e->cyc))//=?
		{
			del_and_update(e, &(e->prc_lst), 0);
			if (e->prc_lst == 0)
				return (0);
			check_lives(e);//if check_lives < 0 break ;
		}
		e->cyc_counter += 1;
		e->cyc_since_beg += 1;
		if ((e->speed == 1) || (e->par.print && (e->cyc_since_beg % e->speed == 1)))
			print_map(*e);
		if (e->par.verb & V_2)
			ft_printf("It is now cycle %d\n", e->cyc_since_beg);
		if (do_one_cycle(e) < 0)
			return (ft_error_vm(STR_ERROR_CYCLE));
		if ((e->speed == 1) || (e->par.print && (e->cyc_since_beg % e->speed) == 1))
			ft_wait(e);
		if (e->par.print)
			clear_screen();
		if (e->cyc < 0)
		{
			del_and_update(e, &(e->prc_lst), 1);
			return (0);
		}
	}
	return (0);
}

/*int     run_vm(t_env *e)
{
	while (e->cyc >= -CYCLE_DELTA && e->prc_lst)
	{
		if (e->par.print && (e->cyc_since_beg % e->speed == 0))
			print_map(*e);
		if (do_one_cycle(e) < 0)
			return (ft_error_vm(STR_ERROR_CYCLE));
		e->cyc_counter += 1;
		e->cyc_since_beg += 1;
		if (e->par.verb & V_2)
			ft_printf("It is now cycle %d\n", e->cyc_since_beg);
		if (e->cyc_counter == e->cyc || e->cyc <= 0)//=?
		{
			if (e->cyc > 0)
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
}*/
