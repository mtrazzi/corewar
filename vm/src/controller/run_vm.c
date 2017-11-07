/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_vm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 12:44:40 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/11/05 19:16:32 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "print_ncurses.h"

static void		check_lives(t_env *e)
{
	static u_int last_cyc_number = 0;

	last_cyc_number = e->cyc_since_beg;
	e->cyc_counter = 0;
	if (e->nb_live >= NBR_LIVE)
	{
		e->nb_live = 0;
		e->nb_checks = 0;
		e->cyc -= CYCLE_DELTA;
		if (e->par.opts & OPT_V2)
			ft_printf("Cycle to die is now %d\n", e->cyc);
	}
	else if (e->nb_checks == MAX_CHECKS - 1)
	{
		e->nb_checks = 0;
		e->nb_live = 0;
		e->cyc -= CYCLE_DELTA;
		if (e->par.opts & OPT_V2)
			ft_printf("Cycle to die is now %d\n", e->cyc);
	}
	else
	{
		e->nb_checks += 1;
		e->nb_live = 0;
	}
}

static void		del_and_update_aux(t_env *e, t_dll **prc_lst,
										t_dll **last_alive, int all)
{
	t_prc *prc;

	prc = (t_prc *)((*prc_lst)->content);
	if (prc->live == 0 || all)
	{
		if (e->par.opts & OPT_V8)
			ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
					prc->id, e->cyc_since_beg - prc->cyc_last_live, e->cyc);
		if (e->par.opts & OPT_M)
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

static void		del_and_update(t_env *e, t_dll **begin_lst, int all)
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

int				forward_one_cycle(t_env *e)
{
	e->cyc_counter += 1;
	e->cyc_since_beg += 1;
	if (e->par.opts & OPT_V2)
		ft_printf("It is now cycle %d\n", e->cyc_since_beg);
	if (do_one_cycle(e) < 0)
		return (ft_error_vm(STR_ERROR_CYCLE));
	if (e->cyc <= 0 || e->cyc_counter == (e->cyc < 0 ? -e->cyc : e->cyc))
	{
		if (e->par.opts & OPT_M)
			update_champ(e);
		del_and_update(e, &(e->prc_lst), e->cyc <= 0);
		check_lives(e);
		if (e->prc_lst == 0)
			return (0);
	}
	if ((e->par.opts & OPT_D) && e->cyc_since_beg == e->par.dump_cycle)
		return (dump(e));
	return (1);
}

int				run_vm(t_env *e)
{
	int		ret;

	while (1)
	{
		ret = forward_one_cycle(e);
		if (ret < 0 || ret == 0)
			return (ret);
	}
	return (0);
}
