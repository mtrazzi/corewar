/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 12:05:12 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/09/10 12:09:31 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

#define BYTES_PER_LINE 64
#define END_OF_COLOR "\e[0m"
#define PRINT_NB_CYC 1

static	void	change_color_prc(t_env *e, int incr)
{
	t_dll *prc_lst;
	t_prc *prc;

	prc_lst = e->prc_lst;
	while (prc_lst)
	{
		prc = (t_prc *)(prc_lst->content);
		e->map_color[prc->pc].color += incr;
		prc_lst = prc_lst->next;
	}
}

void			print_map(t_env e)
{
	int		nb_bytes;
	int		j;
	char	*color;

	nb_bytes = 0;
	change_color_prc(&e, 1);
	if (PRINT_NB_CYC)
		printf("NB OF CYCLES SINCE BEGINNING : %d\nCYCLES PER STEP : %d\n",
				e.cyc_since_beg - 1, e.spd);
	while (nb_bytes < MEM_SIZE)
	{
		j = 0;
		while (j < BYTES_PER_LINE)
		{
			color = g_color_tab[e.map_color[nb_bytes + j].color];
			printf("%s%02x%s ", color, e.map[nb_bytes + j], END_OF_COLOR);
			j++;
		}
		printf("\n");
		nb_bytes += BYTES_PER_LINE;
	}
	change_color_prc(&e, -1);
}

void			print_introduction(t_env *e)
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

void			print_conclusion(t_env *e)
{
	u_int i;
	t_chp chp;

	i = 0;
	while (i < e->par.nb_chp)
	{
		chp = e->par.champions[i];
		if (chp.nb == e->last_alive)
			printf("Contestant %d, \"%s\", has won !\n", i + 1, chp.name);
		i++;
	}
}

void			print_adv(t_env *e, int pos, int skip)
{
	int i;

	printf("ADV %d (0x%04x -> 0x%04x) ", skip, pos, pos + skip);
	i = -1;
	while (++i < skip)
		printf("%02x ", e->map[mod_map(pos + i)]);
	printf("\n");
}
