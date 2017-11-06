/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opts_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 21:37:57 by pkirsch           #+#    #+#             */
/*   Updated: 2017/11/03 21:38:15 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "opts.h"

int			is_empty_op(t_opts *opt)
{
	int	i;

	i = -1;
	while (++i < opt->nb_param)
	{
		if (opt->params[i].arg != NULL)
			return (0);
	}
	return (1);
}
