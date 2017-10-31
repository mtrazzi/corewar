/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laranda <laranda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 12:35:54 by laranda           #+#    #+#             */
/*   Updated: 2017/10/31 22:47:50 by laranda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "print_ncurses.h"

int g_log_fd = -1;

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

void 	init_log()
{
	g_log_fd = open("log_ncurse", O_WRONLY | O_CREAT);
	if (g_log_fd < 0)
	{
		ft_printf("%s\n", "CEST TRES LERREUR DE LOG\n");
		exit(-1010101);
	}
}

void	refresh_fields(WINDOW **fields)
{
	int		i;

	i = -1;
	while (++i < TH_NB)
	{
		wnoutrefresh(fields[i]);
	}
}

void	set_fields(WINDOW **fields, int size[])
{
	int		i;

	i = -1;
	while (++i < TH_NB)
	{
		fields[i] = create_winbox(size[0] / TH_NB, size[1], size[2] + ((size[0] / TH_NB) * i), size[3]);
	}
}

int		print_ncurses(t_env *e)
{
	t_view_env	v_e;

	init_log();

	v_e.status = 1;
	v_e.step = 50;
	v_e.hide = 0;
	while (v_e.status == 1)
	{
		init_ncurses();
		set_fields(v_e.fields, (int[]){66, 195, 1, 3});
		// v_e.field = create_winbox(66, 195, 1, 3);
		v_e.logo = create_winbox(10, 60, 1, 200);
		v_e.infos = create_winbox(42, 60, 11, 200);
		v_e.help = create_winbox(14, 60, 53, 200);
		launch_mthread_fill_field(&v_e, e);
		fill_logo(v_e.logo);
		fill_infos(&v_e, e, 0);
		fill_help(v_e.help);
		// wnoutrefresh(v_e.field);
		refresh_fields(v_e.fields);
		wnoutrefresh(v_e.logo);
		wnoutrefresh(v_e.infos);
		wnoutrefresh(v_e.help);
		doupdate();
		print_worker(e, &v_e);
		endwin();
	}
	if (g_log_fd > 0)
		close(g_log_fd);
	return (v_e.status);
}
