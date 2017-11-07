/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bomberman.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philippe <Philippe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 14:05:48 by pkirsch           #+#    #+#             */
/*   Updated: 2017/11/07 14:23:31 by Philippe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

#define BPL BYTES_PER_LINE
#define RADIUS 6
#define BOMB_MSG ("Bomb has been planted, escaping the site")

static void	kill_zone(t_env *e, u_int pos, t_prc *prc)
{
	t_dll	*current;
	t_dll	*tmp;
	t_prc	*tmp_prc;

	current = e->prc_lst;
	while (current)
	{
		tmp = current->next;
		tmp_prc = (t_prc *)current->content;
		if (mod_map(tmp_prc->pc) == pos
				&& tmp_prc->id != prc->id)
		{
			if (current == e->prc_lst)
				e->prc_lst = current->next;
			dll_delone(&current);
		}
		current = tmp;
	}
}

static void	reset_color(t_env *e, u_int pos, t_prc *prc)
{
	e->map_color[pos].color = 0;
	e->map_color[pos].is_prc = 0;
	e->map_color[pos].prc_count = 0;
	e->map_color[pos].color_live = 0;
	e->map_color[pos].live_count = 0;
	e->map[pos] = 0;
	kill_zone(e, pos, prc);
}

int			bomberman(t_env *e, t_prc *prc)
{
	int	r;
	int pos;
	int x_y[2];

	r = RADIUS + 1;
	pos = prc->pc;
	x_y[1] = 0;
	while (--r > 0)
	{
		x_y[0] = -r - 1;
		while (++(x_y[0]) < r)
		{
			if (pos + x_y[1] + x_y[0] <= MEM_SIZE
					&& (pos + x_y[1]) / BPL == (pos + x_y[1] + x_y[0]) / BPL)
				reset_color(e, mod_map(pos + x_y[1] + x_y[0]), prc);
			if (pos - x_y[1] + x_y[0] >= 0
					&& (pos - x_y[1]) / BPL == (pos - x_y[1] + x_y[0]) / BPL)
				reset_color(e, mod_map(pos - x_y[1] + x_y[0]), prc);
		}
		x_y[1] += BPL;
	}
	if (e->par.opts & OPT_V4)
		ft_printf("P %4d | %s +%d\n", BOMB_MSG, prc->id, RADIUS + 1);
	prc->pc = mod_map(prc->pc + RADIUS + 1);
	return (1);
}
