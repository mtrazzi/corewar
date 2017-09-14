/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laranda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 12:35:54 by laranda           #+#    #+#             */
/*   Updated: 2017/09/13 12:35:55 by laranda          ###   ########.fr       */
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

// static	void	change_color_prc(t_env *e, int incr)
// {
// 	t_dll *prc_lst;
// 	t_prc *prc;

// 	prc_lst = e->prc_lst;
// 	while (prc_lst)
// 	{
// 		prc = (t_prc *)(prc_lst->content);
// 		e->map_color[prc->pc] += incr;
// 		prc_lst = prc_lst->next;
// 	}
// }

void	fill_field(WINDOW *field, t_env *e)
{
	int		nb_bytes;
	int		j;
	// char	*color;

	nb_bytes = 0;
	// change_color_prc(&e, 1);
	// if (PRINT_NB_CYC)
	// 	printf("NB OF CYCLES SINCE BEGINNING : %d\nCYCLES PER STEP : %d\n",
	// 			e.cyc_since_beg - 1, e.spd);
	while (nb_bytes < MEM_SIZE)
	{
		j = 0;
		while (j < BYTES_PER_LINE)
		{
			// color = g_color_tab[e.map_color[nb_bytes + j]];
			// printf("%s%02x%s ", color, e.map[nb_bytes + j], END_OF_COLOR);
			mvwprintw(field, 1 + (nb_bytes / BYTES_PER_LINE), 2 + (j * 3), "%02x ", e->map[nb_bytes + j]);
			j++;
		}
		mvwprintw(field, nb_bytes % 64, 64, "\n");
		nb_bytes += BYTES_PER_LINE;
	}
	// change_color_prc(&e, -1);
}

// void	print_ncurses(t_env *e)
void	print_ncurses(t_env *e)
{
	WINDOW		*field;
	WINDOW		*infos;
	int			key;

	// setlocale(LC_ALL, "");
	initscr();
	cbreak();
	keypad(stdscr, TRUE);
	noecho();
	curs_set(0);
	refresh();
	field = create_winbox(66, 195, 1, 3);
	infos = create_winbox(66, 80, 1, 199);
	fill_field(field, e);
	wrefresh(field);
	wrefresh(infos);
	while ((key = getch()) != 'q')
	{
		if (key == KEY_RESIZE)
		{
			endwin();
			print_ncurses(e);
			return ;
		}
	}
	endwin();
}

// int		main(void)
// {
// 	print_ncurses();
// 	return (0);
// }