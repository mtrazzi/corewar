/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 15:34:24 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/06/02 14:51:26 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*elt;
	void	*tmp;

	if ((elt = (t_list *)malloc(sizeof(t_list *))) == NULL)
		return (NULL);
	if (content == NULL)
	{
		elt->content = NULL;
		elt->content_size = 0;
		elt->next = 0;
		return (elt);
	}
	if ((tmp = malloc(content_size)) == NULL)
		return (NULL);
	elt->content = ft_strdup((char *)content);
	elt->content_size = content_size;
	elt->next = 0;
	return (elt);
}
