/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_infos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laranda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 14:52:28 by laranda           #+#    #+#             */
/*   Updated: 2017/10/30 14:52:29 by laranda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "print_ncurses.h"

void	fill_logo(WINDOW *logo)
{
	wattron(logo, COLOR_PAIR(COLOR_FWHITE));
	mvwaddstr(logo, 2, 10, "   ___               __    __           ");
	mvwaddstr(logo, 3, 10, "  / __\\___  _ __ ___/ / /\\ \\ \\__ _ _ __ ");
	mvwaddstr(logo, 4, 10, " / /  / _ \\| '__/ _ \\ \\/  \\/ / _` | '__|");
	mvwaddstr(logo, 5, 10, "/ /__| (_) | | |  __/\\  /\\  / (_| | |   ");
	mvwaddstr(logo, 6, 10, "\\____/\\___/|_|  \\___| \\/  \\/ \\__,_|_|   ");
	mvwaddstr(logo, 8, 15, "by mtrazzi, pkirsch and laranda");
	wattroff(logo, COLOR_PAIR(COLOR_FWHITE));
}

void	fill_infos(t_view_env *v_e, t_env *e, int running)
{
	u_int	x;

	wattron(v_e->infos, COLOR_PAIR(COLOR_FWHITE));
	mvwprintw(v_e->infos, 1, 2, "** %s **", running ? "RUNNING" : "PAUSED");
	wclrtoeol(v_e->infos);
	mvwprintw(v_e->infos, 3, 2, "Cycles/second limit : %d", v_e->speed);
	wclrtoeol(v_e->infos);
	mvwprintw(v_e->infos, 6, 2, "Cycle : %d", e->cyc_since_beg);
	mvwprintw(v_e->infos, 8, 2, "Processes : %d", dll_size(e->prc_lst));
	x = print_players(v_e->infos, e, 10);
	mvwprintw(v_e->infos, x + 1, 2, "CYCLE_TO_DIE : %d", e->cyc);
	mvwprintw(v_e->infos, x + 3, 2, "CYCLE_DELTA : %d", CYCLE_DELTA);
	mvwprintw(v_e->infos, x + 5, 2, "NBR_LIVE : %d", NBR_LIVE);
	mvwprintw(v_e->infos, x + 7, 2, "MAX_CHECKS : %d", MAX_CHECKS);
	wattroff(v_e->infos, COLOR_PAIR(COLOR_FWHITE));
	box(v_e->infos, 0, 0);
}

u_int	print_players(WINDOW *win, t_env *e, u_int x)
{
	u_int		i;
	t_prc		*champ_prc;

	i = 0;
	while (i < e->par.nb_chp)
	{
		champ_prc = get_prc_by_champ(e, i + 1);
		mvwprintw(win, x, 2, "Player %d :", e->par.champions[i].nb);
		wattron(win, COLOR_PAIR(i + 1));
		mvwprintw(win, x, 15, "%s", e->par.champions[i].name);
		mvwprintw(win, x + 1, 2, "%.58s", e->par.champions[i].comment);
		wattroff(win, COLOR_PAIR(i + 1));
		wattron(win, COLOR_PAIR(COLOR_FWHITE));
		if (champ_prc)
		{
			mvwprintw(win, x + 2, 2,
						"  Last Live : %29d", champ_prc->cyc_last_live);
			mvwprintw(win, x + 3, 2, "  Lives in current period : %15d",
				champ_prc->live);
		}
		wclrtoeol(win);
		i++;
		x += 5;
	}
	return (x);
}

void	fill_help(WINDOW *help)
{
	wattron(help, COLOR_PAIR(COLOR_FWHITE));
	mvwaddstr(help, 1, 26, "COMMANDS");
	mvwaddstr(help, 3, 2, "Next Cycle :        N");
	mvwaddstr(help, 4, 2, "Run / Pause :   Space");
	mvwaddstr(help, 6, 2, "GoTo :              G");
	mvwaddstr(help, 7, 2, "         then cycle # and Enter");
	mvwaddstr(help, 3, 42, "Speed :");
	mvwaddstr(help, 4, 35, "-10   -1   +1   +10");
	mvwaddstr(help, 5, 35, " E     R    T     Y");
	mvwaddstr(help, 9, 2, "Quit :              Q");
	wattroff(help, COLOR_PAIR(COLOR_FWHITE));
}
