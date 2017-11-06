/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_vm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 11:44:29 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/09/10 11:44:49 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	ft_free_vm_env(t_env *e)
{
	t_dll *next;

	while (e->prc_lst)
	{
		next = e->prc_lst->next;
		free(e->prc_lst->content);
		free(e->prc_lst);
		e->prc_lst = next;
	}
	return (1);
}
