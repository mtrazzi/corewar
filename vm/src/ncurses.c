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

int	is_prc(t_env *e, u_int pos)
{
	t_dll *prc_lst;
	t_prc *prc;

	prc_lst = e->prc_lst;
	while (prc_lst)
	{
		prc = (t_prc *)(prc_lst->content);
		if (prc->pc == pos)
			return (1);
		prc_lst = prc_lst->next;
	}
	return (0);
}

void	init_color_pairs()
{
	init_pair(COLOR_ZEROS, COLOR_ZEROS, COLOR_BLACK);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(10, COLOR_BLACK, COLOR_GREEN);
	init_pair(20, COLOR_BLACK, COLOR_BLUE);
	init_pair(30, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(40, COLOR_BLACK, COLOR_YELLOW);
}

int		get_color_pair(t_env *e, u_int pos)
{
	int		color_pair;

	color_pair = e->map_color[pos].color;
	if (is_prc(e, pos))
		color_pair *= 10;
	return (color_pair ? color_pair : COLOR_ZEROS);
}

void	fill_field(WINDOW *field, t_env *e)
{
	int		nb_bytes;
	int		j;
	int 	color;

	nb_bytes = 0;
	init_color_pairs();
	while (nb_bytes < MEM_SIZE)
	{
		j = 0;
		while (j < BYTES_PER_LINE)
		{
			color = get_color_pair(e, nb_bytes + j);
			wattron(field, COLOR_PAIR(color));
			mvwprintw(field, 1 + (nb_bytes / BYTES_PER_LINE), 2 + (j * 3), "%02x", e->map[nb_bytes + j]);
			wattroff(field, COLOR_PAIR(color));
			j++;
		}
		nb_bytes += BYTES_PER_LINE;
	}
}

void	fill_infos(WINDOW *infos, t_env *e, int loop)
{
	mvwprintw(infos, 1, 2, "** %s **", loop ? "RUNNING" : "PAUSED");
	mvwprintw(infos, 3, 2, "Cycles/second limit : 50");
	mvwprintw(infos, 6, 2, "Cycle : %d", e->cyc_since_beg);
	mvwprintw(infos, 8, 2, "Processes : %d", dll_size(e->prc_lst));
}

int		forward_one_cycle(t_env *e, WINDOW *field, WINDOW *infos, int loop)
{
	e->cyc_counter += 1;
	e->cyc_since_beg += 1;	
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

	fill_field(field, e);
	fill_infos(infos, e, loop);
	wrefresh(field);
	wrefresh(infos);

	return 1;
}

int		running_loop(t_env *e, WINDOW *field, WINDOW *infos, int speed)
{
	int			key;
	int 		status;

	while ((key = getch()) != ' ' && key != 'q' && status == 1)
	{
		usleep(speed);
		status = forward_one_cycle(e, field, infos, 1);
	}
	return status;
}

int		print_worker(t_env *e, WINDOW *field, WINDOW *infos)
{
	int			key;
	int 		status;
	int			speed;

	speed = 50;
	
	status = 1;
	while ((key = getch()) != 'q' && status == 1)
	{
		if (key == ' ')
		{
			nodelay(stdscr, TRUE);
			if((status = running_loop(e, field, infos, speed)) != 1)
				return status;
			nodelay(stdscr, FALSE);
		}
		else if (key == 'n')
			status = forward_one_cycle(e, field, infos, 1);
		else if (key == KEY_RESIZE)
			return (1);
		if (key == 'q')
			return 0;
		fill_infos(infos, e, 0);
		wrefresh(infos);
	}
	return status > 0 ? 0 : status;
}


int		print_ncurses(t_env *e)
{
	WINDOW		*field;
	WINDOW		*infos;
	int			status;	

	status = 1;
	while (status == 1)
	{
		initscr();
		start_color();
		cbreak();
		keypad(stdscr, TRUE);
		noecho();
		curs_set(0);
		refresh();
		field = create_winbox(66, 195, 1, 3);
		infos = create_winbox(66, 80, 1, 200);
		fill_field(field, e);
		fill_infos(infos, e, 0);
		wrefresh(field);
		wrefresh(infos);
		status = print_worker(e, field, infos);
		endwin();
	}
	return status;
}
