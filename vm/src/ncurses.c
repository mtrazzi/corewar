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
	init_pair(5, COLOR_GREEN3, COLOR_BLACK);
	init_pair(6, COLOR_BLUE3, COLOR_BLACK);
	init_pair(7, COLOR_MAGENTA3, COLOR_BLACK);
	init_pair(8, COLOR_YELLOW3, COLOR_BLACK);
	init_pair(11, COLOR_WHITE, COLOR_GREEN);
	init_pair(12, COLOR_WHITE, COLOR_BLUE);
	init_pair(13, COLOR_WHITE, COLOR_MAGENTA);
	init_pair(14, COLOR_WHITE, COLOR_YELLOW);
	init_pair(10, COLOR_BLACK, COLOR_GREEN);
	init_pair(20, COLOR_BLACK, COLOR_BLUE);
	init_pair(30, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(40, COLOR_BLACK, COLOR_YELLOW);
}

int		get_color_pair(t_env *e, u_int pos)
{
	int		color_pair;

	color_pair = e->map_color[pos].color;
	if (e->map_color[pos].live_count)
	{
		color_pair += 10;
		e->map_color[pos].live_count--;
	}
	else if (e->map_color[pos].prc_count)
	{
		color_pair += 4;
		e->map_color[pos].prc_count--;
	}
	else if (is_prc(e, pos) && !e->map_color[pos].live_count)
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

void	fill_infos(t_view_env *v_e, t_env *e, int loop)
{
	mvwprintw(v_e->infos, 1, 2, "** %s **", loop ? "RUNNING" : "PAUSED");
	mvwprintw(v_e->infos, 3, 2, "Cycles/second limit : %d", v_e->speed);
	mvwprintw(v_e->infos, 6, 2, "Cycle : %d", e->cyc_since_beg);
	mvwprintw(v_e->infos, 8, 2, "Processes : %d", dll_size(e->prc_lst));
}

int		forward_one_cycle(t_env *e, t_view_env *v_e, int loop)
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

	fill_field(v_e->field, e);
	fill_infos(v_e, e, loop);
	wrefresh(v_e->field);
	wrefresh(v_e->infos);

	return 1;
}

void	control_speed(t_view_env *v_e)
{
	struct timespec				now;
	unsigned long long 			t2;
	useconds_t					sleep_time;

	clock_gettime(CLOCK_REALTIME, &now);
	t2 = (now.tv_nsec / 1000) + (now.tv_sec * 1000000);
	if (v_e->t)
	{
	    sleep_time = (useconds_t)((1000000 / v_e->speed) - (t2 - v_e->t));
	    if (sleep_time > 0)
	    	usleep(sleep_time);
	}
	v_e->t = t2;
}

void	check_speed_key(int key, t_view_env *v_e)
{
	if (key == 'r')
		v_e->speed += 1;
	else if (key == 't')
		v_e->speed += 10;
	else if (key == 'e')
		v_e->speed -= 1;
	else if (key == 'w')
		v_e->speed -= 10;
	if (v_e->speed <= 0)
		v_e->speed = 1;
}

int		running_loop(t_env *e, t_view_env *v_e)
{
	int							key;

	while ((key = getch()) != ' ' && key != 'q' && v_e->status == 1)
	{
		check_speed_key(key, v_e);
		// control_speed(v_e);
		v_e->status = forward_one_cycle(e, v_e, 1);
	}
	return v_e->status;
}

void	print_worker(t_env *e, t_view_env *v_e)
{
	int			key;
	
	while ((key = getch()) != 'q' && v_e->status == 1)
	{
		if (key == ' ')
		{
			nodelay(stdscr, TRUE);
			v_e->status = running_loop(e, v_e);
			nodelay(stdscr, FALSE);
		}
		else if (key == 'n')
			v_e->status = forward_one_cycle(e, v_e, 1);
		else if (key == KEY_RESIZE)
			return ;
		check_speed_key(key, v_e);
		fill_infos(v_e, e, 0);
		wrefresh(v_e->infos);
		if (key == 'q')
			v_e->status = 0;
	}
	v_e->status = v_e->status > 0 ? 0 : v_e->status;
}


int		print_ncurses(t_env *e)
{
	t_view_env	v_e;

	v_e.status = 1;
	v_e.speed = 50;
	v_e.t = 0;
	while (v_e.status == 1)
	{
		initscr();
		start_color();
		cbreak();
		keypad(stdscr, TRUE);
		noecho();
		curs_set(0);
		refresh();
		v_e.field = create_winbox(66, 195, 1, 3);
		v_e.infos = create_winbox(66, 80, 1, 200);
		fill_field(v_e.field, e);
		fill_infos(&v_e, e, 0);
		wrefresh(v_e.field);
		wrefresh(v_e.infos);
		print_worker(e, &v_e);
		endwin();
	}
	return v_e.status;
}
