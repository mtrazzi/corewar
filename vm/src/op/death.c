/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 17:57:33 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/09/10 17:57:48 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	death(t_env *e, t_prc *prc)
{
	int ret;

	prc->live -= 1;
	prc->live_nb = get_value(e, DIR_CODE, prc, prc->pc + 1);
	e->nb_live = (e->nb_live == 0 ? 0 : e->nb_live -1);
	if (e->par.verb & V_4)
		printf("P %4d | death %d\n", prc->id, prc->live_nb);
	if ((ret = is_real_number(e, prc->live_nb)) > 0)
	{
		e->last_alive = prc->live_nb;
		if (e->par.verb & V_1)
			printf("Player %d (%s) has been killed\n",
			ret, e->par.champions[ret - 1].name);
	}
	return (0);
}
