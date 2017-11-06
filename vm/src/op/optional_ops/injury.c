/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 17:57:33 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/11/05 19:54:30 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	injury(t_env *e, t_prc *prc)
{
	int ret;


	prc->live = 0;
	prc->live_nb = get_value(e, DIR_CODE, prc, prc->pc + 1);
	if (e->par.opts & OPT_V4)
		printf("P %4d | death %d\n", prc->id, prc->live_nb);
	if ((ret = is_real_number(e, prc->live_nb)) > 0)
	{
		if (e->par.opts & OPT_V1)
			printf("Player %d (%s) suffered an injury\n",
					ret, e->par.champions[ret - 1].name);
	}
	return (0);
}
