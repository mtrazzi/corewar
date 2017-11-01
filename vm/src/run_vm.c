/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_vm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 12:44:40 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/09/10 15:36:56 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "print_ncurses.h"


static void	ft_wait(t_env *e)
{
	char *line;
	char *rem;

	line = NULL;
	rem = NULL;
	while (!line || ft_strcmp(line, "s"))
	{
		get_next_line(0, &line, &rem);
		if (!ft_strcmp(line, "r"))
			e->spd += 5;
		else if (!ft_strcmp(line, "l"))
			e->spd -= 5;
		else if (ft_is_int(line))
			e->spd = ft_atoi(line);
		print_map(*e);
	}
}

void	check_lives(t_env *e)
{
	static u_int last_cyc_number = 0;

	last_cyc_number = e->cyc_since_beg;
	e->cyc_counter = 0;
	if (e->nb_live >= NBR_LIVE)
	{
		e->nb_live = 0;
		e->nb_checks = 0;
		e->cyc -= CYCLE_DELTA;
		if (e->par.verb & V_2)
			printf("Cycle to die is now %d\n", e->cyc);
	}
	else if (e->nb_checks == MAX_CHECKS - 1)
	{
		e->nb_checks = 0;
		e->nb_live = 0;
		e->cyc -= CYCLE_DELTA;
		if (e->par.verb & V_2)
			printf("Cycle to die is now %d\n", e->cyc);
	}
	else
	{
		e->nb_checks += 1;
		e->nb_live = 0;
	}
}

static void	del_and_update_aux(t_env *e, t_dll **prc_lst, t_dll **last_alive,
																	int all)
{
	t_prc *prc;

	prc = (t_prc *)((*prc_lst)->content);
	if (prc->live == 0 || all)
	{
		if (e->par.verb & V_8)
			printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
					prc->id, e->cyc_since_beg - prc->cyc_last_live, e->cyc);
		if (e->par.print)
			e->map_color[mod_map(prc->pc)].is_prc = 0;
		dll_delone(prc_lst);
	}
	else if (!(*last_alive))
		*last_alive = *prc_lst;
	if (*prc_lst)
	{
		prc->live = 0;
		prc->live_nb = 0;
	}
}

void	del_and_update(t_env *e, t_dll **begin_lst, int all)
{
	t_dll *prc_lst;
	t_dll *next;
	t_dll *last_alive;

	prc_lst = *begin_lst;
	last_alive = NULL;
	while (prc_lst)
	{
		next = prc_lst->next;
		del_and_update_aux(e, &prc_lst, &last_alive, all);
		prc_lst = next;
	}
	*begin_lst = last_alive;
}

int			run_vm(t_env *e)
{
	while (1)
	{
		if (e->par.print)
			return (print_ncurses(e));
		else
		{
			e->cyc_counter += 1;
			e->cyc_since_beg += 1;
			if (e->par.verb & V_2)
				printf("It is now cycle %d\n", e->cyc_since_beg);
			if (do_one_cycle(e) < 0)
				return (ft_error_vm(STR_ERROR_CYCLE));
			if (e->cyc < 0 || e->cyc_counter == (e->cyc < 0 ? -e->cyc : e->cyc))
			{
				del_and_update(e, &(e->prc_lst), e->cyc < 0);
				check_lives(e);
				if (e->prc_lst == 0)
					return (0);
			}
			if (e->par.dump && e->cyc_since_beg == e->par.nb_cyc)
				return (dump(e));
		}
	}
	return (0);
}








