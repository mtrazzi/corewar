/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 18:16:21 by pkirsch           #+#    #+#             */
/*   Updated: 2017/08/23 18:16:39 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dll.h"

t_dll	*get_last(t_dll *lst)
{
	if (!lst)
		return (lst);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_dll	*get_first(t_dll *lst)
{
	return (lst);
}

/*
**	n is 0-indexed
*/

t_dll	*get_n(t_dll *lst, u_int n)
{
	u_int	count;

	count = 0;
	while (count++ < n && lst)
		lst = lst->next;
	return (lst);
}
