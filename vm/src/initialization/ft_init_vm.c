/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_vm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 11:47:07 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/11/06 19:06:29 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	init_chp(t_chp *chp)
{
	chp->nb = 0;
	ft_bzero(chp->name, PROG_NAME_LENGTH + 1);
	ft_bzero(chp->comment, COMMENT_LENGTH + 1);
	chp->file_name = NULL;
	chp->cyc_last_live = 0;
	chp->total_lives_since_period_beg = 0;
}

static void	init_champions(t_env *e)
{
	int i;

	i = -1;
	while (++i < MAX_PLAYERS)
		init_chp(&(e->par.champions[i]));
}

int			ft_init_vm(t_env *e)
{
	ft_bzero(e->map, MEM_SIZE);
	ft_bzero(e->map_color, MEM_SIZE * sizeof(t_color));
	e->prc_lst = NULL;
	e->cyc = CYCLE_TO_DIE;
	e->cyc_counter = 0;
	e->nb_live = 0;
	e->nb_checks = 0;
	e->par.opts = 0;
	e->par.dump_cycle = 0;
	e->par.nb_chp = 0;
	e->cyc_since_beg = 0;
	e->last_alive = 0;
	e->spd = 5;
	e->total_prc = 0;
	e->max_prc = 0;
	init_champions(e);
	return (1);
}
