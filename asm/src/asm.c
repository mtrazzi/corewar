/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 20:15:55 by pkirsch           #+#    #+#             */
/*   Updated: 2017/09/28 19:14:00 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	init_header(header_t *h)
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

int			main(int ac, char **av)
{
	t_asm a;

	init_asm(&a);
	if (ac != 2)
		return (-1 * ft_fprintf(2, "usage: ./asm champions_file.s\n"));
	if (open_file(av[1], &a.fd) != 1)
		return (-1);
	if (get_labels(&a) != 1)
		return (-1 * clear_asm(&a));
	close(a.fd);
	if ((a.fd = open(av[1], O_RDONLY)) < 0)
		return (-1 * clear_asm(&a) * reopen_error(av[1]));
	if (parsing(&a) != 1)
		return (-1 * clear_asm(&a));
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
