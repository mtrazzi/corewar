/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_bytecode.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 18:24:39 by pkirsch           #+#    #+#             */
/*   Updated: 2017/09/29 17:33:55 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**	int i = -1;
** 	while (++i < 16)
**		tab[i] = 0xff;//change that!
*/

void		print_header(t_asm *a)
{
	char	tab[16];
	int		paddings[2];
	int		mod;

	mod = (sizeof(a->header.magic) + PROG_NAME_LENGTH) % 8;
	paddings[0] = 8 - (mod == 0 ? 8 : mod);
	mod = (sizeof(a->header.magic) + PROG_NAME_LENGTH
			+ sizeof(a->header.prog_size) + COMMENT_LENGTH + paddings[0]) % 16;
	paddings[1] = 16 - (mod == 0 ? 16 : mod);
	ft_bzero(tab, 16);
	write_be(a->fd, a->header.magic, sizeof(a->header.magic));
	write(a->fd, a->header.prog_name, PROG_NAME_LENGTH);
	write(a->fd, tab, paddings[0]);
	write_be(a->fd, a->header.prog_size, sizeof(a->header.prog_size));
	write(a->fd, a->header.comment, COMMENT_LENGTH);
	write(a->fd, tab, paddings[1]);
}

static int	write_op(t_dll *dll, void *data)
{
	t_ope	*ope;
	int		fd;
	int		i;

	ope = (t_ope *)dll->content;
	fd = (int)data;
	write_be(fd, ope->op_code, 1);
	if (ope->op_tab_x->ocp > 0)
		write_be(fd, ope->ocp, 1);
	i = -1;
	while (++i < MAX_ARGS_NUMBER)
	{
		if (ope->type_param[i] & T_REG)
			write_be(fd, ope->params[i], PAR_SIZE_REG);//(int)?
		else if (ope->type_param[i] & T_IND)
			write_be(fd, ope->params[i], PAR_SIZE_IND);
		else if (ope->type_param[i] & T_DIR)
			write_be(fd, ope->params[i], 4 - 2 * ope->op_tab_x->label_size);
	}
	return (1);
}

void		print_cmds(t_asm *a)
{
	if (a->ops)
		dll_iter_int(a->ops, write_op, (void *)(long)a->fd);
}
