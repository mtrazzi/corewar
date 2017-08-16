/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/22 15:40:06 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/08/14 10:12:23 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_open(char *file_name)
{
	int fd;

	if ((fd = open(file_name, O_RDONLY)) == -1)
	{
		ft_putstr("Error : cannot open file\n");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int		ft_nb_lines(char *file_name)
{
	int		fd;
	int		sum;
	char	*line;

	sum = 0;
	fd = ft_open(file_name);
	while (get_next_line(fd, &line) > 0)
		sum++;
	if (close(fd) == -1)
		exit(EXIT_FAILURE);
	return (sum);
}

int		ft_tab_length(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}
