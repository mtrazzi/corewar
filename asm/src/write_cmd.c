/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 18:27:26 by pkirsch           #+#    #+#             */
/*   Updated: 2017/09/28 18:52:29 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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
