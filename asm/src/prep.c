/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 18:17:52 by pkirsch           #+#    #+#             */
/*   Updated: 2017/09/29 14:28:48 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "limits.h"

static int	cmp_line_nb_label_line(t_dll *e, void *data)
{
	if (((t_ope *)e->content)->line_nb >= (u_int)(*(long *)data))
		return (0);
	return (1);
}

static int	cmp_associate(t_dll *e, void *data)
{
	long	tmp;
	t_dll	*ope;

	tmp = ((t_sym *)e->content)->line_number_parsing_help;
	ope = dll_iter_dll(data, cmp_line_nb_label_line, &tmp);
	if (ope != NULL)
	{
		((t_sym *)e->content)->c_ope = (t_ope *)ope->content;
	}
	else
		((t_sym *)e->content)->c_ope = NULL;
	return (1);
}

static int	calc_sizes(t_dll *ops)
{
	if (!ops)
		return (1);
	dll_foreach_content(ops, nb_bytes_op);
	dll_foreach(ops, calc_add_size);
	return (1);
}

static int	rsbv(t_dll *dll, void *data)
{
	t_dll	*dlltmp;
	t_dll	*syms;
	int		i;
	t_ope	*ope;

	dlltmp = NULL;
	syms = data;
	ope = (t_ope *)dll->content;
	i = -1;
	while (++i < ope->nb_param)
	{
		if (!(ope->type_param[i] & T_LAB))
			continue ;
		dlltmp = dll_iter_dll(syms, get_sym_by_sym,
								(void *)(long)ope->params[i]);
		if (dlltmp != NULL && ((t_sym *)dlltmp->content)->c_ope)
			ope->params[i] = ((t_sym *)dlltmp->content)->c_ope->ais - ope->ais;
		else if (dlltmp != NULL)
			ope->params[i] = ((t_ope *)get_last(dll)->content)->ais +
							((t_ope *)get_last(dll)->content)->size - ope->ais;
		dlltmp = NULL;
	}
	return (1);
}

int			prep(t_asm *a)
{
	u_long size;

	if (a->syms && a->ops)
		dll_iter_dll(a->syms, cmp_associate, a->ops);
	calc_sizes(a->ops);
	if (a->syms && a->ops)
		dll_iter_int(a->ops, rsbv, a->syms);
	size = a->ops ? ((t_ope *)get_last(a->ops)->content)->ais
							+ ((t_ope *)get_last(a->ops)->content)->size
					: 0;
	if (size > UINT_MAX)
		return (-1 * ft_fprintf(2, "prog_size > UINT_MAX\n"));
	a->header.prog_size = size;
	return (1);
}
