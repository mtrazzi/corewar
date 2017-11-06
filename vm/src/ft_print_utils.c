/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 12:05:12 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/11/06 14:03:39 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	print_introduction(t_env *e)
{
	u_int i;
	t_chp chp;

	printf("%s\n", "Introducing contestants...");
	i = 0;
	while (i < e->par.nb_chp)
	{
		chp = e->par.champions[i];
		printf("* Player %d, weighing %u bytes, \"%s\" (\"%s\") !\n",\
				i + 1, chp.prog_size, chp.name, chp.comment);
		i++;
	}
}

void	print_conclusion(t_env *e)
{
	u_int i;
	t_chp chp;

	i = 0;
	while (i < e->par.nb_chp)
	{
		chp = e->par.champions[i];
		if (chp.nb == e->last_alive)
		{
			printf("Contestant %d, \"%s\", has won !\n", i + 1, chp.name);
			return ;
		}
		i++;
	}
	printf("Contestant %d, \"%s\", has won !\n", i, chp.name);
}

void	print_adv(t_env *e, int pos, int skip)
{
	int i;

	printf("ADV %d (0x%04x -> 0x%04x) ", skip, pos, pos + skip);
	i = -1;
	while (++i < skip)
		printf("%02x ", e->map[mod_map(pos + i)]);
	printf("\n");
}
