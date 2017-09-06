/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_del.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 18:14:17 by pkirsch           #+#    #+#             */
/*   Updated: 2017/09/06 19:11:19 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dll.h"

void	dll_delone_f(t_dll **to_del, t_del *f)
{
	if (!to_del || !(*to_del))
		return ;
	if ((*to_del)->prev)
		(*to_del)->prev->next = (*to_del)->next;
	if ((*to_del)->next)
		(*to_del)->next->prev = (*to_del)->prev;
	(*to_del)->prev = NULL;
	(*to_del)->next = NULL;
	if ((*to_del)->content && f)
		f(&((*to_del)->content));
	free((*to_del));
	*to_del = NULL;
}

void	dll_del_f(t_dll **lst, t_del *f)
{
	t_dll *tmp;

	if (!lst || !(*lst))
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		dll_delone_f(&(*lst), f);
		*lst = tmp;
	}
	*lst = NULL;
}

#include <stdio.h>
void	dll_delone(t_dll **to_del)
{
	printf("SUPPR\nSUPPR\nSUPPR\nSUPPR\n");
	if (!to_del || !(*to_del))
		return ;
	if ((*to_del)->prev)
		(*to_del)->prev->next = (*to_del)->next;
	if ((*to_del)->next)
		(*to_del)->next->prev = (*to_del)->prev;
	(*to_del)->prev = NULL;
	(*to_del)->next = NULL;
	if ((*to_del)->content)
		free((*to_del)->content);
	(*to_del)->content = NULL;
	free((*to_del));
	*to_del = NULL;
}

void	dll_del(t_dll **lst)
{
	t_dll *tmp;

	if (!lst || !(*lst))
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		dll_delone(&(*lst));
		*lst = tmp;
	}
	*lst = NULL;
}
