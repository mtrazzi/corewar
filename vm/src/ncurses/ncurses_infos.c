/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_infos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laranda <laranda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 14:52:28 by laranda           #+#    #+#             */
/*   Updated: 2017/11/07 16:33:35 by laranda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "print_ncurses.h"

static void	print_vm_stats(t_view_env *v_e, t_env *e)
{
	u_int	x;
	int		nb_prc;

	x = BKDN_LINE - 15;
	nb_prc = dll_size(e->prc_lst);
	e->max_prc = nb_prc > e->max_prc ? nb_prc : e->max_prc;
	mvwprintw(v_e->infos, x, 25, "[VM STATS]");
	mvwprintw(v_e->infos, x + 2, 2, "Cycle : %d", e->cyc_since_beg);
	mvwprintw(v_e->infos, x + 2, 35, "Step by : %d cycles", v_e->step);
	wclrtoeol(v_e->infos);
	mvwprintw(v_e->infos, x + 3, 2, "Cycle to die : %d", e->cyc);
	wclrtoeol(v_e->infos);
	mvwprintw(v_e->infos, x + 4, 2, "Processes : %d", nb_prc);
	wclrtoeol(v_e->infos);
	mvwprintw(v_e->infos, x + 5, 2, "Total Processes : %d", e->total_prc);
	mvwprintw(v_e->infos, x + 6, 2, "Max Processes : %d", e->max_prc);
	mvwprintw(v_e->infos, x + 4, 35, "CYCLE_DELTA : %d", CYCLE_DELTA);
	mvwprintw(v_e->infos, x + 5, 35, "NBR_LIVE : %d", NBR_LIVE);
	mvwprintw(v_e->infos, x + 6, 35, "MAX_CHECKS : %d", MAX_CHECKS);
	print_progress_bar(v_e->infos, e, x + 9, MSG_PROGRESS_BAR);
}

static void	print_players(WINDOW *win, t_env *e, u_int x)
{
	u_int		i;
	u_int		pos;

	i = 0;
	while (i < e->par.nb_chp)
	{
		mvwprintw(win, x, 2, "Player %d : %n", e->par.champions[i].nb, &pos);
		wattron(win, COLOR_PAIR(i + 1));
		mvwprintw(win, x, 2 + pos, "%.*s", 44 - pos, e->par.champions[i].name);
		mvwprintw(win, x + 1, 2, "%.44s", e->par.champions[i].comment);
		wattroff(win, COLOR_PAIR(i + 1));
		wattron(win, COLOR_PAIR(COLOR_FWHITE));
		mvwprintw(win, x + 2, 2,
				"  Last Live : %29d", e->par.champions[i].cyc_last_live);
		mvwprintw(win, x + 3, 2, "  Lives in current period : %15d",
						e->par.champions[i].total_lives_since_period_beg);
		wclrtoeol(win);
		i++;
		x += 5;
	}
}

void		fill_infos(t_view_env *v_e, t_env *e, int running)
{
	wattron(v_e->infos, COLOR_PAIR(COLOR_FWHITE));
	mvwprintw(v_e->infos, 2, 24, "** %s **", running ? "RUNNING" : "PAUSED");
	wclrtoeol(v_e->infos);
	print_vm_stats(v_e, e);
	wattron(v_e->infos, COLOR_PAIR(COLOR_FWHITE));
	mvwprintw(v_e->infos, BKDN_LINE - 2, 22, "[CHAMPIONS STATS]");
	print_breakdown(v_e->infos, e, BKDN_LINE, MSG_CURRENT_PERIOD);
	wattron(v_e->infos, COLOR_PAIR(COLOR_FWHITE));
	print_players(v_e->infos, e, BKDN_LINE + 7);
	wattroff(v_e->infos, COLOR_PAIR(COLOR_FWHITE));
	box(v_e->infos, 0, 0);
}

void		print_winner(t_env *e, t_view_env *v_e)
{
	u_int	i;
	t_chp	chp;
	int		key;

	i = 0;
	refill_field(v_e, e);
	chp = e->par.champions[i];
	while (++i < e->par.nb_chp && chp.nb != e->last_alive)
		chp = e->par.champions[i];
	wattron(v_e->infos, COLOR_PAIR(i));
	mvwprintw(v_e->infos, 1, 2, "PLAYER %d, %s, HAS WON !", i, chp.name);
	wmove(v_e->infos, 2, 1);
	wclrtoeol(v_e->infos);
	wattroff(v_e->infos, COLOR_PAIR(i));
	mvwprintw(v_e->infos, 3, 2, "(press Q to quit)");
	box(v_e->infos, 0, 0);
	wrefresh(v_e->infos);
	while ((key = getch()) != 'q')
		;
}
