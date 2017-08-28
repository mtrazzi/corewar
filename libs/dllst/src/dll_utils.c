/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 18:17:36 by pkirsch           #+#    #+#             */
/*   Updated: 2017/08/23 18:19:08 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dll.h"

int	is_in_dll(t_dll *lst, t_dll *to_extract)
{
	while (lst)
	{
		if (lst == to_extract)
			return (1);
		lst = lst->next;
	}
	return (0);
}
