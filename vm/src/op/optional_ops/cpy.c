/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 19:07:17 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/11/02 20:25:36 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	copy(t_env *e, t_prc *prc)
{
	int	nb_1;
	int	nb_2;
	int	nb_3;

	nb_1 = e->map[mod_map(prc->pc + 2)];
	nb_2 = e->map[mod_map(prc->pc + 3)];
	nb_3 = e->map[mod_map(prc->pc + 4)];
	prc->r[nb_3] = prc->r[nb_1];
	prc->r[nb_2] = prc->r[nb_1];
	prc->carry = (prc->r[nb_1] == 0);
	if (e->par.opts & OPT_V4)
		ft_printf("P %4d | copy r%d in r%d and r%d\n", prc->id, nb_1, nb_2, nb_3);
	return (0);
}
