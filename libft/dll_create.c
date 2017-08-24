/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 17:44:03 by pkirsch           #+#    #+#             */
/*   Updated: 2017/08/24 12:59:21 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dll.h"
#include "ft_printf.h"

#define STD_ERROR 2
#define DEBUG_DLL 0

t_dll	*dll_new(void *content)
{
	t_dll	*new;

	new = (t_dll *)malloc(sizeof(t_dll));
	if (new == NULL)
	{
		//if (DEBUG_DLL == 1)
		//	ft_fprintf(STD_ERROR, "malloc in dll_new failed\n");
		return (0);
	}
	new->content = content;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
