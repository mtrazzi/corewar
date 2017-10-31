/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_field.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laranda <laranda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 21:55:05 by laranda           #+#    #+#             */
/*   Updated: 2017/10/31 22:52:18 by laranda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "print_ncurses.h"

static void		th_create_err(int error, t_view_env *v_e)
{
	int id;

	if (error == 11)
		ft_fprintf(2, "Insufficient resources to create thread\n");
	else if (error == 22)
		ft_fprintf(2, "Invalid setting of attr.\n");
	else if (error == 1)
		ft_fprintf(2, "None of permissions needed.\n");
	id = -1;
	while (++id < TH_NB)
		pthread_detach(v_e->th[id].pth);
	// ft_exit(e);
}

static void		th_join_err(int error, t_view_env *v_e)
{
	int id;

	if (error == 35)
		ft_fprintf(2, "A Deadlock was detected.\n");
	else if (error == 22)
		ft_fprintf(2, "thread is not a joinable thread");
	else if (error == 3)
		ft_fprintf(2, "No thread with this id could be found.\n");
	id = -1;
	while (++id < TH_NB)
		pthread_detach(v_e->th[id].pth);
	// ft_exit(e);
}

void	*th_fill_field(void *param)
{
	t_th	*th;
	// int		start;
	// int		end;
	
	th = (t_th *)param;
	// start = (MEM_SIZE / TH_NB) * th->id;
	// end = (MEM_SIZE / TH_NB) * (th->id + 1);
	// fill_field(th->v_e, th->e, start, end);
	fill_field(th->v_e, th->e, th->v_e->fields[th->id], th->id);
	return (NULL);
}

int				launch_mthread_fill_field(t_view_env *v_e, t_env *e)
{
	int	i;
	int ret;

	i = -1;
	while (++i < TH_NB)
	{
		v_e->th[i].id = i;
		v_e->th[i].e = e;
		v_e->th[i].v_e = v_e;
		ret = pthread_create(&(v_e->th[i].pth), NULL, th_fill_field, &(v_e->th[i]));
		if (ret != 0)
			th_create_err(ret, v_e);
	}
	i = -1;
	while (++i < TH_NB)
	{
		ret = pthread_join(v_e->th[i].pth, NULL);
		if (ret != 0)
			th_join_err(ret, v_e);
	}
	return (1);
}

void	fill_field(t_view_env *v_e, t_env *e, WINDOW *field, int id)
{
	int		nb_bytes;
	int		j;
	int		color;
	int		offset;

	nb_bytes = 0;
	offset = (MEM_SIZE / TH_NB) * id;
	if (!v_e->hide)
	{
		while (nb_bytes < MEM_SIZE / TH_NB)
		{
			j = 0;
			while (j < BYTES_PER_LINE)
			{
				color = get_color_pair(e, nb_bytes + j);
				wattron(field, COLOR_PAIR(color));
				mvwprintw(field, 1 + (nb_bytes / BYTES_PER_LINE), 2 + (j * 3),
							"%02x", e->map[nb_bytes + offset + j]);
				wattroff(field, COLOR_PAIR(color));
				j++;
			}
			nb_bytes += BYTES_PER_LINE;
		}
	}
}
