/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_controls.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laranda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 14:53:50 by laranda           #+#    #+#             */
/*   Updated: 2017/10/30 14:53:51 by laranda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "print_ncurses.h"

int		forward_one_cycle(t_env *e, t_view_env *v_e)
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
	fill_infos(v_e, e, 1);
	wnoutrefresh(v_e->field);
	wnoutrefresh(v_e->infos);
	doupdate();
	return (1);
}

void	control_speed(t_view_env *v_e)
{
	struct timespec				now;
	unsigned long long			t2;
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
	if (key == 't')
		v_e->speed += 1;
	else if (key == 'y')
		v_e->speed += 10;
	else if (key == 'r')
		v_e->speed -= 1;
	else if (key == 'e')
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
		v_e->status = forward_one_cycle(e, v_e);
	}
	return (v_e->status);
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
			v_e->status = forward_one_cycle(e, v_e);
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
