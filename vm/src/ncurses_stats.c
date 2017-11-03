/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_stats.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laranda <laranda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 18:22:33 by laranda           #+#    #+#             */
/*   Updated: 2017/11/03 19:25:34 by laranda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "print_ncurses.h"

void 	init_breakdown(WINDOW *win, u_int x, char *msg)
{
	wattron(win, COLOR_PAIR(COLOR_FWHITE));
	mvwprintw(win, x, 2, "%s", msg);
	wattron(win, COLOR_PAIR(COLOR_ZEROS));
	mvwprintw(win, x + 1, 2, BKDN);
	wattroff(win, COLOR_PAIR(COLOR_ZEROS));
}

void	print_breakdown(WINDOW *win, t_env *e, u_int x, char *msg)
{
	u_int		i;
	u_int		pos;
	float		limit;
	u_int		offset;

	i = 0;
	pos = 0;
	limit = 0.0;
	offset = 0;
	init_breakdown(win, x, msg);
	while (i < e->par.nb_chp)
	{
		wattron(win, COLOR_PAIR(i + 1));
		if (e->nb_live)
		{
			limit = ((float)e->par.champions[i].total_lives_since_period_beg
						* 54.0) / (float)e->nb_live;
		}
		while (pos < 54 && pos < limit + offset)
			mvwprintw(win, x + 1, 3 + pos++, "-");
		offset = pos;
		wattroff(win, COLOR_PAIR(++i));
	}
}
