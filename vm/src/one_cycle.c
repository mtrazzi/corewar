/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cycle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 11:51:55 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/11/05 17:35:57 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

#define STR_ERROR_PROCESS ("Error while handling a process")

int	do_one_cycle(t_env *e)
{
	t_dll *elt;

	elt = e->prc_lst;
	while (elt)
	{
		if (do_process(e, elt->content) < 0)
			return (ft_error_vm(STR_ERROR_PROCESS));
		elt = elt->next;
	}
	return (0);
}
