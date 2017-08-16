/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 16:59:43 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/06/02 15:05:31 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*elt;
	t_list	*rec;

	if (lst == NULL)
		return (NULL);
	if ((elt = ft_lstnew(f(lst)->content, f(lst)->content_size)) == NULL)
		return (NULL);
	rec = ft_lstmap(lst->next, f);
	elt->next = rec;
	return (elt);
}
