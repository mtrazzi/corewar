/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creates.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 18:04:46 by pkirsch           #+#    #+#             */
/*   Updated: 2017/09/29 17:34:35 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_sym	*create_sym(char *label, u_int symbol)
{
	t_sym	*new;

	new = (t_sym *)malloc(sizeof(t_sym));
	if (new == NULL)
		return (NULL);
	new->label = label;
	new->sym = symbol;
	return (new);
}

static t_ope	*create_ope(void)
{
	t_ope	*new;

	new = (t_ope *)malloc(sizeof(t_ope));
	if (new == NULL)
		return (NULL);
	return (new);
}

static t_ope	*create_ope_from_ope_and_ref(t_ope *ope, t_op *ref)
{
	t_ope	*new;

	if ((new = create_ope()) == NULL)
		return (NULL);
	new->nb_param = ref->nb_param;
	ft_memcpy(new->type_param, ope->type_param,
				sizeof(u_int) * MAX_ARGS_NUMBER);
	ft_memcpy(new->params, ope->params, sizeof(u_int) * MAX_ARGS_NUMBER);
	new->op_code = ref->op_code;
	new->size = 0;
	new->ais = 0;
	new->op_tab_x = ope->op_tab_x;
	new->line_nb = ope->line_nb;
	new->ocp = 0;
	return (new);
}

t_dll			*create_ope_dll(t_ope *ope, t_op *ref)
{
	t_ope	*new_ope;
	t_dll	*new_dll;

	if ((new_ope = create_ope_from_ope_and_ref(ope, ref)) == NULL)
		return (NULL);
	if ((new_dll = dll_new((void *)new_ope)) == NULL)
	{
		ft_free((void *)&new_ope);
		return (NULL);
	}
	return (new_dll);
}

t_dll			*create_add_label(char *str, int len, t_dll **syms,
									u_int symbol)
{
	char	*label;
	t_sym	*new_sym;
	t_dll	*new_dll;

	if ((label = ft_strsub(str, 0, len)) == NULL)
		return (NULL);
	if ((new_sym = create_sym(label, symbol)) == NULL)
	{
		(void)ft_free((void *)&label);
		return (NULL);
	}
	if ((new_dll = dll_new((void*)new_sym)) == NULL)
	{
		(void)(ft_free((void *)&label) * ft_free((void *)&new_sym));
		return (NULL);
	}
	dll_append(syms, new_dll);
	return (new_dll);
}
