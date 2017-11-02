/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 11:55:15 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/11/02 19:34:15 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

#define STR_ERR_NB_CHP	("too many champions")
#define BAD_FILE_EXT	("champions filename must end with '.cor'")

int		is_valid_ext(char *file_name)
{
	if (ft_strcmp(file_name + (ft_strlen(file_name) - 4), ".cor") == 0)
		return (1);
	return (0 * ft_error(BAD_FILE_EXT));
}

int		ft_parse_chp(t_env *e, char *file_name, int chp_nb)
{
	t_chp	new_chp;
	u_int	i;

	i = 0;
	while (i < e->par.nb_chp)
		if (chp_nb == e->par.champions[i++].nb)
			return (-1);
	if (++(e->par.nb_chp) > MAX_PLAYERS)
		return (ft_error(STR_ERR_NB_CHP));
	new_chp.nb = chp_nb;
	new_chp.file_name = file_name;
	e->par.champions[e->par.nb_chp - 1] = new_chp;
	return (1);
}
