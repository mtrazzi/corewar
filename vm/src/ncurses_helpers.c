/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laranda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 11:46:58 by laranda           #+#    #+#             */
/*   Updated: 2017/10/30 11:47:02 by laranda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "print_ncurses.h"

int		is_prc(t_env *e, u_int pos)
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

t_prc	*get_prc_by_champ(t_env *e, int id)
{
	t_dll	*prc;

	prc = e->prc_lst;
	while (prc)
	{
		if (((t_prc*)prc->content)->id == id)
			return ((t_prc*)prc->content);
		prc = prc->next;
	}
	return (NULL);
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
	if (is_prc(e, pos) && !e->map_color[pos].live_count)
		color_pair *= 10;
	return (color_pair ? color_pair : COLOR_ZEROS);
}
