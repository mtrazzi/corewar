/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_infos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laranda <laranda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 14:52:28 by laranda           #+#    #+#             */
/*   Updated: 2017/11/03 18:50:29 by laranda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "print_ncurses.h"

void	fill_infos(t_view_env *v_e, t_env *e, int running)
{
	u_int	x;

	wattron(v_e->infos, COLOR_PAIR(COLOR_FWHITE));
	mvwprintw(v_e->infos, 1, 2, "** %s **", running ? "RUNNING" : "PAUSED");
	wclrtoeol(v_e->infos);
	mvwprintw(v_e->infos, 3, 2, "Step by : %d cycles", v_e->step);
	wclrtoeol(v_e->infos);
	mvwprintw(v_e->infos, 6, 2, "Cycle : %d", e->cyc_since_beg);
	mvwprintw(v_e->infos, 7, 2, "Cycle to die : %d", e->cyc);
	wclrtoeol(v_e->infos);
	mvwprintw(v_e->infos, 8, 2, "Processes : %d", dll_size(e->prc_lst));
	wclrtoeol(v_e->infos);
	print_breakdown(v_e->infos, e, 10, MSG_CURRENT_PERIOD);
	wattron(v_e->infos, COLOR_PAIR(COLOR_FWHITE));
	x = print_players(v_e->infos, e, 16);
	mvwprintw(v_e->infos, x + 1, 2, "CYCLE_DELTA : %d", CYCLE_DELTA);
	mvwprintw(v_e->infos, x + 3, 2, "NBR_LIVE : %d", NBR_LIVE);
	mvwprintw(v_e->infos, x + 5, 2, "MAX_CHECKS : %d", MAX_CHECKS);
	// DEBUG
		mvwprintw(v_e->infos, x + 1, 30, "cyc - cyc_counter : %d", e->cyc - e->cyc_counter);
		mvwprintw(v_e->infos, x + 3, 40, "cyc_counter : %d", e->cyc_counter);
	// DEBUG
	wattroff(v_e->infos, COLOR_PAIR(COLOR_FWHITE));
	box(v_e->infos, 0, 0);
}

u_int	print_players(WINDOW *win, t_env *e, u_int x)
{
	u_int		i;
	u_int		pos;

	i = 0;
	while (i < e->par.nb_chp)
	{
		mvwprintw(win, x, 2, "Player %d : %n", e->par.champions[i].nb, &pos);
		wattron(win, COLOR_PAIR(i + 1));
		mvwprintw(win, x, 2 + pos, "%s", e->par.champions[i].name);
		mvwprintw(win, x + 1, 2, "%.58s", e->par.champions[i].comment);
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
	return (x);
}

void	fill_help(WINDOW *help)
{
	wattron(help, COLOR_PAIR(COLOR_FWHITE));
	mvwaddstr(help, 1, 26, "CONTROLS");
	mvwaddstr(help, 3, 2, "Next Cycle :        N");
	mvwaddstr(help, 4, 2, "Step n cycles :     S");
	mvwaddstr(help, 5, 2, "Run / Pause :   Space");
	mvwaddstr(help, 6, 2, "GoTo :              G");
	mvwaddstr(help, 7, 2, "         then cycle # and Enter");
	mvwaddstr(help, 9, 2, "Hide Dump :         H");
	mvwaddstr(help, 3, 38, "Step size :");
	mvwaddstr(help, 4, 35, "-10   -1   +1   +10");
	mvwaddstr(help, 5, 35, " E     R    T     Y");
	mvwaddstr(help, 11, 2, "Quit :              Q");
	wattroff(help, COLOR_PAIR(COLOR_FWHITE));
}

void	print_winner(t_env *e, t_view_env *v_e)
{
	u_int	i;
	t_chp	chp;
	int		key;

	i = 0;
	refill_field(v_e, e);
	while (i < e->par.nb_chp)
	{
		chp = e->par.champions[i];
		if (chp.nb == e->last_alive)
		{
			wattron(v_e->infos, COLOR_PAIR(i + 1));
			mvwprintw(v_e->infos, 1, 2, "PLAYER %d, %s, HAS WON !",
						i + 1, chp.name);
			wattroff(v_e->infos, COLOR_PAIR(i + 1));
			mvwprintw(v_e->infos, 2, 2, "(press Q to quit)");
		}
		i++;
	}
	wnoutrefresh(v_e->field);
	wnoutrefresh(v_e->infos);
	doupdate();
	while ((key = getch()) != 'q')
		;
}
