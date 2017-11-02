/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laranda <laranda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 12:35:54 by laranda           #+#    #+#             */
/*   Updated: 2017/10/31 23:31:51 by laranda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "print_ncurses.h"

void	fill_field(t_view_env *v_e, t_env *e)
{
	int		nb_bytes;
	int		j;
	int		color;

	nb_bytes = 0;
	if (!v_e->hide)
	{
		while (nb_bytes < MEM_SIZE)
		{
			j = 0;
			while (j < BYTES_PER_LINE)
			{
				color = get_color_pair(e, nb_bytes + j);
				wattron(v_e->field, COLOR_PAIR(color));
				mvwprintw(v_e->field, 1 + (nb_bytes / BYTES_PER_LINE),
							2 + (j * 3), "%02x", e->map[nb_bytes + j]);
				wattroff(v_e->field, COLOR_PAIR(color));
				j++;
			}
			nb_bytes += BYTES_PER_LINE;
		}
	}
	else
		decrement_color_mods(e);
}

void	init_ncurses(void)
{
	initscr();
	start_color();
	init_color_pairs();
	cbreak();
	keypad(stdscr, TRUE);
	noecho();
	curs_set(0);
	refresh();
}

int		print_ncurses(t_env *e)
{
	t_view_env	v_e;

	v_e.status = 1;
	v_e.step = 50;
	v_e.hide = 0;
	while (v_e.status == 1)
	{
		init_ncurses();
		v_e.field = create_winbox(66, 195, 1, 3);
		v_e.logo = create_winbox(10, 60, 1, 200);
		v_e.infos = create_winbox(42, 60, 11, 200);
		v_e.help = create_winbox(14, 60, 53, 200);
		fill_field(&v_e, e);
		fill_logo(v_e.logo);
		fill_infos(&v_e, e, 0);
		fill_help(v_e.help);
		wnoutrefresh(v_e.field);
		wnoutrefresh(v_e.logo);
		wnoutrefresh(v_e.infos);
		wnoutrefresh(v_e.help);
		doupdate();
		print_worker(e, &v_e);
		endwin();
	}
	return (v_e.status);
}
