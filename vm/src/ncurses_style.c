/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_style.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laranda <laranda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 11:50:32 by laranda           #+#    #+#             */
/*   Updated: 2017/11/05 18:47:23 by laranda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "print_ncurses.h"

WINDOW	*create_winbox(int height, int width, int starty, int startx)
{
	WINDOW		*win;

	win = newwin(height, width, starty, startx);
	box(win, 0, 0);
	return (win);
}

void	init_color_pairs(void)
{
	init_pair(COLOR_ZEROS, COLOR_ZEROS, COLOR_BLACK);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(5, COLOR_GREEN3, COLOR_BLACK);
	init_pair(6, COLOR_BLUE3, COLOR_BLACK);
	init_pair(7, COLOR_MAGENTA3, COLOR_BLACK);
	init_pair(8, COLOR_YELLOW3, COLOR_BLACK);
	init_pair(11, COLOR_FWHITE, COLOR_GREEN);
	init_pair(12, COLOR_FWHITE, COLOR_BLUE);
	init_pair(13, COLOR_FWHITE, COLOR_MAGENTA);
	init_pair(14, COLOR_FWHITE, COLOR_YELLOW);
	init_pair(COLOR_FWHITE, COLOR_FWHITE, COLOR_BLACK);
	init_pair(10, COLOR_BLACK, COLOR_GREEN);
	init_pair(20, COLOR_BLACK, COLOR_BLUE);
	init_pair(30, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(40, COLOR_BLACK, COLOR_YELLOW);
	init_pair(50, COLOR_ZEROS, COLOR_GREEN);
	init_pair(60, COLOR_ZEROS, COLOR_BLUE);
	init_pair(70, COLOR_ZEROS, COLOR_MAGENTA);
	init_pair(80, COLOR_ZEROS, COLOR_YELLOW);
	init_pair(100, COLOR_BLACK, COLOR_ZEROS);
}

int		get_color_pair(t_env *e, u_int pos)
{
	int		color_pair;

	color_pair = e->map_color[pos].color;
	if (e->map_color[pos].live_count > 0)
	{
		color_pair = e->map_color[pos].color_live;
		color_pair += 10;
		e->map_color[pos].live_count--;
	}
	else if (e->map_color[pos].prc_count > 0)
	{
		color_pair += 4;
		e->map_color[pos].prc_count--;
	}
	if (e->map_color[pos].is_prc && !e->map_color[pos].live_count)
	{
		if (!color_pair)
			color_pair = 100;
		else
			color_pair *= 10;
	}
	return (color_pair ? color_pair : COLOR_ZEROS);
}

void	decrement_color_mods(t_env *e)
{
	int		pos;

	pos = 0;
	while (pos < MEM_SIZE)
	{
		if (e->map_color[pos].live_count > 0)
			e->map_color[pos].live_count--;
		if (e->map_color[pos].prc_count > 0)
			e->map_color[pos].prc_count--;
		pos++;
	}
}

void	fill_logo(WINDOW *logo)
{
	wattron(logo, COLOR_PAIR(COLOR_FWHITE));
	mvwaddstr(logo, 1, 10, "   ___               __    __           ");
	mvwaddstr(logo, 2, 10, "  / __\\___  _ __ ___/ / /\\ \\ \\__ _ _ __ ");
	mvwaddstr(logo, 3, 10, " / /  / _ \\| '__/ _ \\ \\/  \\/ / _` | '__|");
	mvwaddstr(logo, 4, 10, "/ /__| (_) | | |  __/\\  /\\  / (_| | |   ");
	mvwaddstr(logo, 5, 10, "\\____/\\___/|_|  \\___| \\/  \\/ \\__,_|_|   ");
	mvwaddstr(logo, 7, 15, "by mtrazzi, pkirsch and laranda");
	wattroff(logo, COLOR_PAIR(COLOR_FWHITE));
}
