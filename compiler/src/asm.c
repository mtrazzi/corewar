/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philippe <Philippe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 20:15:55 by pkirsch           #+#    #+#             */
/*   Updated: 2017/11/07 15:16:21 by Philippe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	init_header(t_header *h)
{
	h->magic = COREWAR_EXEC_MAGIC;
	ft_bzero(h->prog_name, PROG_NAME_LENGTH + 1);
	h->prog_size = 0;
	ft_bzero(h->comment, COMMENT_LENGTH + 1);
	return (1);
}

static int	init_asm(t_asm *a)
{
	a->syms = NULL;
	a->ops = NULL;
	a->to_skip_syms = NULL;
	init_header(&a->header);
	a->fd = 0;
	return (1);
}

static int	ft_close(int fd)
{
	close(fd);
	return (-1);
}

int			main(int ac, char **av)
{
	t_asm a;

	init_asm(&a);
	if (ac != 2)
		return (-1 * ft_fprintf(ERR_OUT, "usage: ./asm champions_file.s\n"));
	if (open_file(av[1], &a.fd) != 1)
		return (-1);
	if (get_labels(&a) != 1)
		return (-1 * clear_asm(&a) * ft_close(a.fd));
	close(a.fd);
	if ((a.fd = open(av[1], O_RDONLY)) < 0)
		return (-1 * clear_asm(&a) * reopen_error(av[1]));
	if (parsing(&a) != 1)
		return (-1 * clear_asm(&a) * ft_close(a.fd));
	close(a.fd);
	if (prep(&a) != 1)
		return (-1 * clear_asm(&a));
	if (update_fd_asm(&a, av[1]) != 1)
		return (-1 * clear_asm(&a));
	print_header(&a);
	print_cmds(&a);
	clear_asm(&a);
	return (0);
}
