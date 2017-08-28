/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 16:44:17 by pkirsch           #+#    #+#             */
/*   Updated: 2017/08/28 16:31:36 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	set_rem(char **rem, char *buff)
{
	char *tmp;

	if (!*rem)
		tmp = ft_strdup(buff);
	else if (!buff)
		tmp = ft_strdup(*rem);
	else
		tmp = ft_strjoin(*rem, buff);
	if (!tmp)
		return (MAL_ERR_GNL);
	if (*rem)
		free(*rem);
	*rem = tmp;
	return (1);
}

int	get_line(char **line, char **rem)
{
	char *new_line;
	char *tmp;

	new_line = ft_strchr(*rem, '\n');
	if (new_line)
	{
		*line = ft_strsub(*rem, 0, new_line - *rem);
		if (*line == 0)
			return (MAL_ERR_GNL);
		tmp = ft_strdup(new_line + 1);
		if (tmp == 0)
			return (MAL_ERR_GNL);
		free(*rem);
		*rem = tmp;
		return (FOUND_LINE);
	}
	return (0);
}

int	read_loop(char buff[], int fd, char **rem, char **line)
{
	int	ret;

	while ((ret = read(fd, buff, BUFF_SIZE)) != 0)
	{
		if (ret < 0)
			return (FAILURE);
		buff[ret] = '\0';
		if (set_rem(rem, buff) == MAL_ERR_GNL)
			return (MAL_ERR_GNL);
		if ((ret = get_line(line, rem)) != 0)
			return (ret);
	}
	return (10);
}

int	get_next_line(int const fd, char **line, char **rem)
{
	int			ret;
	char		buff[BUFF_SIZE + 1];

	if (fd < 0 || !line)
		return (FAILURE);
	if (*(rem) && (ret = get_line(line, rem)) == FOUND_LINE)
		return (FOUND_LINE);
	if (*(rem) && ret == MAL_ERR_GNL)
		return (FAILURE);
	if ((ret = read_loop(buff, fd, rem, line)) != 10)
		return (ret);
	if (*(rem) == NULL)
		return (END_FILE);
	if ((*(rem))[0] == '\0')
		return (END_FILE);
	if (!(*(line) = ft_strdup(*(rem))))
		return (FAILURE);
	(*(rem))[0] = '\0';
	return (FOUND_SOMETHING);
}
