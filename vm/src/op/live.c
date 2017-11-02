/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 14:49:37 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/11/02 21:19:21 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	live(t_env *e, t_prc *prc)
{
	int ret;

	prc->live += 1;
	prc->live_nb = get_value(e, DIR_CODE, prc, prc->pc + 1);
	prc->cyc_last_live = e->cyc_since_beg;
	e->nb_live += 1;
	if (e->par.opts & OPT_V4)
		printf("P %4d | live %d\n", prc->id, prc->live_nb);//
	if ((ret = is_real_number(e, prc->live_nb)) > 0)
	{
		e->last_alive = prc->live_nb;
		if (e->par.opts & OPT_V1)
			printf("Player %d (%s) is said to be alive\n",
					ret, e->par.champions[ret - 1].name);
		if (e->par.opts & OPT_M)
		{
			e->par.champions[ret - 1].cyc_last_live = e->cyc_since_beg;
			e->par.champions[ret - 1].total_lives_since_period_beg += 1;
			e->map_color[mod_map(prc->pc)].color_live = ret;
			e->map_color[mod_map(prc->pc)].live_count = 49;
		}
	}
	return (0);
}
