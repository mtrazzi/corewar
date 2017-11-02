/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mul.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 17:56:27 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/09/10 17:56:29 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	mul(t_env *e, t_prc *prc)
{
	int	nb_1;
	int	nb_2;
	int	nb_3;

	nb_1 = e->map[mod_map(prc->pc + 2)];
	nb_2 = e->map[mod_map(prc->pc + 3)];
	nb_3 = e->map[mod_map(prc->pc + 4)];
	prc->r[nb_3] = prc->r[nb_1] * prc->r[nb_2];
	prc->carry = (prc->r[nb_3] == 0);
	if (e->par.opts & OPT_V4)
		printf("P %4d | mul r%d r%d r%d\n", prc->id, nb_1, nb_2, nb_3);
	return (0);
}
