/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_vm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 11:58:08 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/09/10 12:21:53 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

#define STR_ERR_READ_FILE "could not read .cor file"
#define STR_ERR_CLOSE_FILE "could not close .cor file"
#define STR_ERR_FORMAT_FILE ".cor file not well formated"
#define STR_ERR_MAGIC "magic number incorrect"
#define STR_ERR_SIZE_CHP "champion size to big"
#define STR_ERR_SIZE_CHP2 "could not read size of program defined in header"
#define STR_ERR_SIZE_CHP3 "champion size inferior to header size"

static int		ft_close(int fd)
{
	if (close(fd) < 0)
		ft_perror_vm();
	return (1);
}

static int		parse_header(t_env *e, int i, int fd)
{
	char	buff[4];
	int		padding;
	t_chp	chp;

	chp = e->par.champions[i];
	if (read(fd, (char *)&chp.magic, 4) < 4)
		return (ft_error_vm(STR_ERR_FORMAT_FILE));
	chp.magic = convert_uint(chp.magic);
	if (chp.magic != COREWAR_EXEC_MAGIC)
		return (ft_error_vm(STR_ERR_MAGIC));
	if (read(fd, chp.name, PROG_NAME_LENGTH + 1) < PROG_NAME_LENGTH)
		return (ft_error_vm(STR_ERR_FORMAT_FILE));
	padding = (4 - (PROG_NAME_LENGTH + 1) % 4) % 4;
	if (read(fd, buff, padding) < padding)
		return (ft_error_vm(STR_ERR_FORMAT_FILE));
	if (read(fd, (char *)&chp.prog_size, 4) < 4)
		return (ft_error_vm(STR_ERR_FORMAT_FILE));
	chp.prog_size = convert_uint(chp.prog_size);
	if (read(fd, chp.comment, COMMENT_LENGTH + 1) < COMMENT_LENGTH)
		return (ft_error_vm(STR_ERR_FORMAT_FILE));
	padding = (4 - (COMMENT_LENGTH + 1) % 4) % 4;
	if (read(fd, buff, padding) < padding)
		return (ft_error_vm(STR_ERR_FORMAT_FILE));
	e->par.champions[i] = chp;
	return (0);
}

static int		write_op_on_map(t_env *e, int i, int fd)
{
	t_chp		chp;
	char		buff[MEM_SIZE];
	u_int		j;

	chp = e->par.champions[i];
	if (chp.prog_size > CHAMP_MAX_SIZE)
		return (ft_error_vm(STR_ERR_SIZE_CHP));
	if (read(fd, buff, chp.prog_size) < chp.prog_size)
		return (ft_error_vm(STR_ERR_SIZE_CHP2));
	j = 0;
	while (j < chp.prog_size)
	{
		e->map[(MEM_SIZE / e->par.nb_chp) * i + j] = buff[j];
		e->map_color[(MEM_SIZE / e->par.nb_chp) * i + j].color = i + 1;
		j++;
	}
	return (0);
}

static int		parse_file(t_env *e, int i)
{
	int fd;

	if ((fd = open(e->par.champions[i].file_name, O_RDONLY)) < 0)
		return (ft_perror_vm());
	if (parse_header(e, i, fd) < 0)
		return (ft_close(fd) * ft_error_vm(STR_ERR_FORMAT_FILE));
	if (write_op_on_map(e, i, fd) < 0)
		return (ft_close(fd) * ft_error_vm(STR_ERR_FORMAT_FILE));
	if (close(fd) < 0)
		return (ft_perror_vm());
	return (0);
}

int				parse_all_files(t_env *e)
{
	u_int i;

	i = 0;
	while (i < e->par.nb_chp)
	{
		if (parse_file(e, i) < 0)
			return (ft_error_vm(STR_ERR_READ_FILE));
		i++;
	}
	return (1);
}
