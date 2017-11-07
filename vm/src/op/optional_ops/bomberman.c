/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bomberman.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philippe <Philippe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 14:05:48 by pkirsch           #+#    #+#             */
/*   Updated: 2017/11/07 13:42:07 by Philippe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

#define BPL BYTES_PER_LINE
#define RADIUS 20

void	kill_zone(t_env *e, u_int pos, t_prc *prc)
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

void	reset_color(t_env *e, u_int pos, t_prc *prc)
{
	e->map_color[pos].color = 0;//
	e->map_color[pos].is_prc = 0;
	e->map_color[pos].prc_count = 0;
	e->map_color[pos].color_live = 0;
	e->map_color[pos].live_count = 0;
	e->map[pos] = 0;
	kill_zone(e, pos, prc);
}

u_int	escape_route(u_int pos)
{
	u_int i;

	i = 1;
	while (i < RADIUS && pos / BPL == (pos + i) / BPL)
		i++;
	return (i);
}


int		bomberman(t_env *e, t_prc *prc)
{
	int	r;
	int pos;
	int y;
	int x;

	r = RADIUS + 1;
	pos = prc->pc;
	y = 0;
	while (--r > 0)
	{
		x = -r - 1;
		while (++x < r)
		{
			if (mod_map(pos + y) - pos < MEM_SIZE / 2
					&& (pos + y) / BPL == (pos + y + x) / BPL)
				reset_color(e, mod_map(pos + y + x), prc);
			if (pos - mod_map(pos - y) < MEM_SIZE / 2
					&& (pos - y) / BPL == (pos - y + x) / BPL)
				reset_color(e, mod_map(pos - y + x), prc);
		}
		y += BPL;
	}
	if (e->par.opts & OPT_V4)
		ft_printf("P %4d | Bomb has been planted, escaping the site +%d\n",
					prc->id, RADIUS + 1);//
	// prc->pc = mod_map(prc->pc + RADIUS + 1);
	prc->pc = mod_map(escape_route(prc->pc));
	return (1);
}
