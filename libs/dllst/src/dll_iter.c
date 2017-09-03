/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_iter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 18:47:37 by pkirsch           #+#    #+#             */
/*   Updated: 2017/09/03 20:14:56 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dll.h"

/*
**	rename
**	dll_cmp_int
**	dll_cmp_dll
**	build
**	void	dll_iter(t_dll *dll, t_cmp cmp, void *data)
*/

int		dll_iter_int(t_dll *dll, t_cmp cmp, void *compare_against)
{
	if (!dll)
		return (0);
	while (dll)
	{
		if (cmp(dll, compare_against) == 0)
			return (1);
		dll = dll->next;
	}
	return (0);
}

t_dll	*dll_iter_dll(t_dll *dll, t_cmp cmp, void *compare_against)
{
	if (!dll)
		return (NULL);
	while (dll)
	{
		if (cmp(dll, compare_against) == 0)
			return (dll);
		dll = dll->next;
	}
	return (NULL);
}

int		dll_foreach_content(t_dll *dll, t_do f)
{
	if (!dll)
		return (0);
	while (dll)
	{
		if (f(dll->content) == 0)
			return (1);
		dll = dll->next;
	}
	return (0);
}

int		dll_foreach(t_dll *dll, t_do f)
{
	if (!dll)
		return (0);
	while (dll)
	{
		if (f(dll) == 0)
			return (1);
		dll = dll->next;
	}
	return (0);
}

int		dll_foreach_tmp(t_dll *dll, t_do f)
{
	t_dll *tmp;

	if (!dll)
		return (0);
	while (dll)
	{
		tmp = dll->next;
		if (f(dll) == 0)
			return (1);
		dll = tmp;
	}
	return (0);
}
