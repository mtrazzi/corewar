/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_transfer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 17:46:51 by pkirsch           #+#    #+#             */
/*   Updated: 2017/08/23 18:27:12 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dll.h"

/*
**	position is 0-indexed
**	if position to big > dont insert ? si
*/

void	dll_insert(t_dll **lst, t_dll *to_insert, u_int position)
{
	t_dll	*ret;

	if (!to_insert || !lst)
		return ;
	if (position == 0 || !(*lst))
	{
		dll_push_front(lst, to_insert);
		return ;
	}
	ret = get_n(*lst, position - 1);
	if (ret == NULL)
	{
		dll_push_back(lst, to_insert);
		return ;
	}
	if (ret->next == NULL)
	{
		dll_push_back(lst, to_insert);
		return ;
	}
	to_insert->next = ret->next;
	to_insert->prev = ret;
	ret->next->prev = to_insert;
	ret->next = to_insert;
}

/*
**	Extract from ptr
**	2 layers, PRIVATE: dll_extract_ptr_pvt(lst, to_ex, check in)
**	dll_extract_ptr(lst, to_ex) calls pvt(lst, to_ex, 1)
**	dll_extract_pos(lst, to_ex) cals pvt(lst, to_ex, 0)
*/

t_dll	*dll_extract_ptr(t_dll **lst, t_dll *to_extract)
{
	if (!lst || !(*lst) || !to_extract)
		return (NULL);
	if (to_extract == get_first(*lst))
		return (dll_pop(lst, DLL_FIRST));
	if (to_extract == get_last(*lst))
		return (dll_pop(lst, DLL_LAST));
	if (!is_in_dll(*lst, to_extract))
		return (NULL);
	to_extract->prev->next = to_extract->next;
	to_extract->next->prev = to_extract->prev;
	to_extract->prev = NULL;
	to_extract->next = NULL;
	return (to_extract);
}

/*
**	Extract from pos
*/

t_dll	*dll_extract_pos(t_dll **lst, u_int position)
{
	if (!lst || !(*lst))
		return (NULL);
	return (dll_extract_ptr(lst, get_n(*lst, position)));
}

/*
** from a to b
*/

void	dll_transfer_ptr(t_dll **lst_a, t_dll **lst_b, t_dll *to_transfer,
							u_int to_position)
{
	t_dll	*extracted;

	extracted = dll_extract_ptr(lst_a, to_transfer);
	dll_insert(lst_b, extracted, to_position);
}

void	dll_transfer_pos(t_dll **lst_a, t_dll **lst_b, u_int from_position,
							u_int to_position)
{
	t_dll	*extracted;

	extracted = dll_extract_pos(lst_a, from_position);
	dll_insert(lst_b, extracted, to_position);
}
