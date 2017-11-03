/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_controls.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laranda <laranda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 14:53:50 by laranda           #+#    #+#             */
/*   Updated: 2017/11/03 18:56:10 by laranda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "print_ncurses.h"

int		forward_one_cycle(t_env *e, t_view_env *v_e)
{
	if (e->cyc - e->cyc_counter == 1)
		print_breakdown(v_e->infos, e, 13, MSG_LAST_PERIOD);
	e->cyc_counter += 1;
	e->cyc_since_beg += 1;
	if (do_one_cycle(e) < 0)
		return (ft_error_vm(STR_ERROR_CYCLE));
	if (e->cyc < 0 || e->cyc_counter == (e->cyc < 0 ? -e->cyc : e->cyc))
	{
		update_champ(e);
		del_and_update(e, &(e->prc_lst), e->cyc < 0);
		check_lives(e);
		if (e->prc_lst == 0)
			return (0);
	}
	fill_field(v_e, e);
	fill_infos(v_e, e, 1);
	wnoutrefresh(v_e->field);
	wnoutrefresh(v_e->infos);
	doupdate();
	return (1);
}

int		running_loop(t_env *e, t_view_env *v_e)
{
	int		key;

	nodelay(stdscr, TRUE);
	while ((key = getch()) != ' ' && key != 'q' && v_e->status == 1)
	{
		check_step_key(key, v_e);
		check_hide(key, v_e, e);
		v_e->status = forward_one_cycle(e, v_e);
	}
	if (key == 'q')
		v_e->status = -1;
	nodelay(stdscr, FALSE);
	return (v_e->status);
}

int		goto_loop(t_env *e, t_view_env *v_e, int cycle)
{
	int		key;

	nodelay(stdscr, TRUE);
	while ((key = getch()) != ' ' && key != 'q' && v_e->status == 1
				&& e->cyc_since_beg < cycle)
	{
		wattron(v_e->infos, COLOR_PAIR(1));
		mvwprintw(v_e->infos, 5, 2, "Going to cycle %d", cycle);
		wattroff(v_e->infos, COLOR_PAIR(1));
		check_hide(key, v_e, e);
		v_e->status = forward_one_cycle(e, v_e);
	}
	wmove(v_e->infos, 5, 1);
	wclrtoeol(v_e->infos);
	if (key == 'q')
		v_e->status = -1;
	nodelay(stdscr, FALSE);
	return (v_e->status);
}

int		do_goto(t_env *e, t_view_env *v_e)
{
	int		cycle;

	cycle = 0;
	wattron(v_e->infos, COLOR_PAIR(1));
	mvwprintw(v_e->infos, 4, 2, "Go to cycle ?");
	wmove(v_e->infos, 4, 17);
	curs_set(2);
	echo();
	noraw();
	wrefresh(v_e->infos);
	mvwscanw(v_e->infos, 4, 17, "%d", &cycle);
	wattroff(v_e->infos, COLOR_PAIR(1));
	noecho();
	raw();
	curs_set(0);
	wmove(v_e->infos, 4, 1);
	wclrtoeol(v_e->infos);
	if (cycle > e->cyc_since_beg)
		v_e->status = goto_loop(e, v_e, cycle);
	return (v_e->status);
}

void	print_worker(t_env *e, t_view_env *v_e)
{
	int			key;

	while (v_e->status == 1 && (key = getch()) != 'q')
	{
		if (key == ' ')
			v_e->status = running_loop(e, v_e);
		else if (key == 'n')
			v_e->status = forward_one_cycle(e, v_e);
		else if (key == 's')
			v_e->status = goto_loop(e, v_e, e->cyc_since_beg + v_e->step);
		else if (key == 'g')
			v_e->status = do_goto(e, v_e);
		else if (key == KEY_RESIZE)
			return ;
		check_step_key(key, v_e);
		check_hide(key, v_e, e);
		fill_infos(v_e, e, 0);
		wrefresh(v_e->infos);
		if (key == 'q')
			v_e->status = -1;
	}
	if (v_e->status == 0)
		print_winner(e, v_e);
	v_e->status = v_e->status > 0 ? 0 : v_e->status;
}
