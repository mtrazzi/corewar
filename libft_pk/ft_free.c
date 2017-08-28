/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 21:01:34 by pkirsch           #+#    #+#             */
/*   Updated: 2017/08/23 21:04:23 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

int		ft_free(void **to_free)
{
	if (to_free && *to_free)
	{
		free(*to_free);
		*to_free = NULL;
	}
	return (1);
}