/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 20:31:04 by Philippe          #+#    #+#             */
/*   Updated: 2017/06/29 19:26:44 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		th_create_err(int error, t_env *e)
{
	int id;

	if (error == 11)
		ft_fprintf(2, "Insufficient resources to create thread\n");
	else if (error == 22)
		ft_fprintf(2, "Invalid setting of attr.\n");
	else if (error == 1)
		ft_fprintf(2, "None of permissions needed.\n");
	id = -1;
	while (++id < TH_NBR)
		pthread_detach(e->th[id].pth);
	ft_exit(e);
}

static void		th_join_err(int error, t_env *e)
{
	int id;

	if (error == 35)
		ft_fprintf(2, "A Deadlock was detected.\n");
	else if (error == 22)
		ft_fprintf(2, "thread is not a joinable thread");
	else if (error == 3)
		ft_fprintf(2, "No thread with this id could be found.\n");
	id = -1;
	while (++id < TH_NBR)
		pthread_detach(e->th[id].pth);
	ft_exit(e);
}

int				launch_mthread_fractals(t_env *e, void *(*f)(void *param))
{
	int	i;
	int ret;

	i = -1;
	while (++i < TH_NBR)
	{
		e->th[i].id = i;
		e->th[i].env = e;
		ret = pthread_create(&(e->th[i].pth), NULL, f, &(e->th[i]));
		if (ret != 0)
			th_create_err(ret, e);
	}
	i = -1;
	while (++i < TH_NBR)
	{
		ret = pthread_join(e->th[i].pth, NULL);
		if (ret != 0)
			th_join_err(ret, e);
	}
	return (1);
}
