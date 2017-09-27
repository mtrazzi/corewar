/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 20:15:55 by pkirsch           #+#    #+#             */
/*   Updated: 2017/09/27 21:14:33 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	init_header(header_t *h)
{
	h->magic = COREWAR_EXEC_MAGIC;
	ft_bzero(h->prog_name, PROG_NAME_LENGTH + 1);
	h->prog_size = 0;
	ft_bzero(h->comment, COMMENT_LENGTH + 1);
	return (1);
}

int	init_asm(t_asm *a)
{
	a->syms = NULL;
	a->ops = NULL;
	a->to_skip_syms = NULL;
	init_header(&a->header);
	a->fd = 0;
	return (1);
}

int main(int ac, char **av)
{
	t_asm a;

	init_asm(&a);
	if (ac != 2)//or open last one ?
		return (-1 * ft_fprintf(2, "usage: ./asm champions_file.s\n"));
	if (open_file(av[1], &a.fd) != 1)
		return (-1);
	init_g_op();
	if (get_labels(&a) != 1)
		return (-1 * clear_asm(&a));
	close(a.fd);
	// ft_printf("DONE\n");
	// sym_dll_print("parsed labels\n", a.syms);
	// sym_dll_print("to_skip labels\n", a.to_skip_syms);
	if ((a.fd = open(av[1], O_RDONLY)) < 0)
		return (-1 * clear_asm(&a) * ft_fprintf(2, "Can't reopen source file '%s'\n", av[1]));
	if (parsing(&a) != 1)
		return (-1 * clear_asm(&a));
	close(a.fd);
	// sym_dll_print("{On_blue}parsed labels{eoc}\n", a.syms);
	// sym_dll_print("{On_blue}to_skip labels{eoc}\n", a.to_skip_syms);
	// dll_print_f("{On_blue}ops{eoc}\n", a.ops, ope_str_);
	ft_printf("name {%s}\n comment {%s}\n", a.header.prog_name, a.header.comment);
	if (prep(&a) != 1)
		return (-1 * clear_asm(&a));
	// sym_dll_print("{On_red}parsed labels{eoc}\n", a.syms);
	// dll_print_f("{On_blue}ops OCP{eoc}\n", a.ops, ope_str_);
	if (update_fd_asm(&a, av[1]) != 1)
		return (-1 * clear_asm(&a));
	print_header(&a);
	print_cmds(&a);
	clear_asm(&a);
	return (0);
}
