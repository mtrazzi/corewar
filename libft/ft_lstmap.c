/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 16:59:43 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/08/17 10:12:02 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*elt;
	t_list	*rec;

	if (!lst)
		return (NULL);
	elt = ft_lstnew(f(lst)->content);
	rec = ft_lstmap(lst->next, f);
	elt->next = rec;
	return (elt);
}
