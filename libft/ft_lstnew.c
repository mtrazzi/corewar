/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 15:34:24 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/08/17 09:52:41 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content)
{
	t_list	*elt;

	elt = (t_list *)ft_memalloc(sizeof(t_list));
	elt->next = NULL;
	if (content == NULL)
		elt->content = NULL;
	else
		elt->content = ft_strdup((char *)content);
	return (elt);
}
