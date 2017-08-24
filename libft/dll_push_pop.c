/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_push_pop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 17:42:26 by pkirsch           #+#    #+#             */
/*   Updated: 2017/08/23 18:19:47 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dll.h"

void	dll_push_front(t_dll **lst, t_dll *new)
{
	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		new->prev = NULL;
		new->next = NULL;
		*lst = new;
		return ;
	}
	new->prev = NULL;
	new->next = (*lst);
	(*lst)->prev = new;
	*lst = new;
}

void	dll_push_back(t_dll **lst, t_dll *new)
{
	t_dll *curr;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		new->prev = NULL;
		new->next = NULL;
		*lst = new;
		return ;
	}
	curr = *lst;
	while (curr->next)
		curr = curr->next;
	curr->next = new;
	new->prev = curr;
	new->next = NULL;
}

void	dll_append(t_dll **lst, t_dll *new)
{
	dll_push_back(lst, new);
}

/*
**	if first == 0: pop_front
**	else: pop_back
*/

t_dll	*dll_pop(t_dll **lst, int first)
{
	t_dll	*ret;

	if (!lst || !(*lst))
		return (NULL);
	if (first == 0)
	{
		ret = get_first(*lst);
		*lst = ret->next;
		if (*lst)
			(*lst)->prev = NULL;
		ret->next = NULL;
		ret->prev = NULL;
		return (ret);
	}
	ret = get_last(*lst);
	if (ret->prev)
		ret->prev->next = NULL;
	else
		*lst = NULL;
	ret->prev = NULL;
	ret->next = NULL;
	return (ret);
}
