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
