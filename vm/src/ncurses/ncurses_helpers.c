/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laranda <laranda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 11:46:58 by laranda           #+#    #+#             */
/*   Updated: 2017/11/05 19:07:32 by laranda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "print_ncurses.h"

void	update_champ(t_env *e)
{
	u_int i;

	i = 0;
	while (i < e->par.nb_chp)
		e->par.champions[i++].total_lives_since_period_beg = 0;
}

void	check_step_key(int key, t_view_env *v_e)
{
	if (key == 't')
		v_e->step += 1;
	else if (key == 'y')
		v_e->step += 10;
	else if (key == 'r')
		v_e->step -= 1;
	else if (key == 'e')
		v_e->step -= 10;
	if (v_e->step <= 0)
		v_e->step = 1;
}

void	check_hide(int key, t_view_env *v_e, t_env *e)
{
	if (key == 'h')
	{
		wclear(v_e->field);
		box(v_e->field, 0, 0);
		if (v_e->hide)
		{
			v_e->hide = 0;
			fill_field(v_e, e);
		}
		else
		{
			v_e->hide = 1;
			mvwprintw(v_e->field, 25, 84, "DUMP HIDDEN (press H to show)");
		}
		wrefresh(v_e->field);
	}
}

void	refill_field(t_view_env *v_e, t_env *e)
{
	if (v_e->hide)
	{
		wclear(v_e->field);
		box(v_e->field, 0, 0);
		v_e->hide = 0;
		fill_field(v_e, e);
		wrefresh(v_e->field);
	}
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
