/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 08:35:44 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/08/17 14:11:34 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int					ft_is_there_fd(int fd, t_line_lst *line_lst)
{
	if (!line_lst)
		return (0);
	while (line_lst && line_lst->fd != fd)
		line_lst = line_lst->next;
	if (line_lst && line_lst->fd == fd)
		return (1);
	return (0);
}

static t_line_lst	*ft_add_line(t_line_lst **line_lst, \
										int fd, char *line)
{
	t_line_lst	*to_add;
	t_line_lst	*begin_lst;

	if (!line)
		return (*line_lst);
	begin_lst = *line_lst;
	to_add = (t_line_lst *)ft_memalloc(sizeof(t_line_lst));
	to_add->line = line;
	to_add->fd = fd;
	to_add->next = NULL;
	if (!(*line_lst))
	{
		*line_lst = to_add;
		return (to_add);
	}
	while ((*line_lst)->next)
		*line_lst = (*line_lst)->next;
	(*line_lst)->next = to_add;
	*line_lst = begin_lst;
	return (begin_lst);
}

static void			ft_get_line(int fd, t_line_lst **line_lst, char **line)
{
	t_line_lst	*begin_lst;
	t_line_lst	*tmp;

	if (!(*line_lst))
	{
		*line = NULL;
		return ;
	}
	begin_lst = *line_lst;
	while ((*line_lst)->fd != fd && (*line_lst)->next->fd != fd)
		*line_lst = (*line_lst)->next;
	if ((*line_lst)->fd == fd)
	{
		*line = ft_strdup((*line_lst)->line);
		*line_lst = (*line_lst)->next;
		ft_strdel(&begin_lst->line);
		ft_memdel((void **)&begin_lst);
		return ;
	}
	*line = ft_strdup((*line_lst)->next->line);
	tmp = (*line_lst)->next;
	(*line_lst)->next = (*line_lst)->next->next;
	ft_strdel(&tmp->line);
	ft_memdel((void **)&tmp);
	*line_lst = begin_lst;
}

static int			ft_get_buffer(int fd, t_line_lst **line_lst)
{
	static char	*result = NULL;
	char		buff[BUFF_SIZE + 1];
	char		*tmp;
	int			ret;

	if (ft_is_there_fd(fd, *line_lst))
		ft_get_line(fd, line_lst, &result);
	while (!ft_strchr(result, '\n') && (ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		tmp = result;
		result = ft_strjoin(result, buff);
		ft_strdel(&tmp);
	}
	tmp = result;
	if (ft_strchr(result, '\n'))
	{
		*(ft_strchr(result, '\n')) = '\0';
		ft_add_line(line_lst, fd, ft_strdup(result));
		ft_add_line(line_lst, fd, ft_strdup(ft_strchr(result, '\0') + 1));
	}
	else
		ft_add_line(line_lst, fd, ft_strdup(result));
	ft_strdel(&tmp);
	return (ret);
}

int					get_next_line(int fd, char **line)
{
	static t_line_lst	*line_lst = NULL;
	int					ret;

	ret = ft_get_buffer(fd, &line_lst);
	if (ret < 0)
		return (-1);
	ft_get_line(fd, &line_lst, line);
	return (**line > 0 || ret);
}
