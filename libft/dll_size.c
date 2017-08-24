/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philippe <Philippe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 18:07:50 by pkirsch           #+#    #+#             */
/*   Updated: 2017/07/28 00:25:26 by Philippe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dll.h"

u_int	dll_size(t_dll *lst)
{
	u_int	count;

	if (!lst)
		return (0);
	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}
