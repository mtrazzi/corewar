/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 16:32:42 by pkirsch           #+#    #+#             */
/*   Updated: 2017/09/29 17:43:02 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static u_int	get_type(char *str)
{
	if (*str == '\0')
		return (NOT_A_PARAM_CODE);
	if (*str == DIRECT_CHAR && *(str + 1) == LABEL_CHAR)
		return (T_LAB | T_DIR);
	if (*str == LABEL_CHAR)
		return (T_LAB | T_IND);
	if (*str == DIRECT_CHAR)
		return (T_DIR);
	if (*str == REG_CHAR)
		return (T_REG);
	if (*str == '-' || ft_isdigit(*str))
		return (T_IND);
	return (NOT_A_PARAM_CODE);
}

static u_int	check_type(char *str, int param_nb, t_op *ref)
{
	u_int type;

	type = get_type(str);
	if (type == NOT_A_PARAM_CODE)
		return (16);
	if ((ref->type_param[param_nb] & type) == 0)
		return (32);
	return (type);
}

static int		check_param(char **str, int param_nb, t_op *ref,
								void *ptrs[2])
{
	u_int ret;

	if ((ret = check_type(*str, param_nb, ref)) & (32 | 16))
		return (ret);
	((t_ope *)ptrs[0])->type_param[param_nb] = ret;
	if (ret == T_REG && get_reg(str, param_nb, ptrs[0]) != 1)
		return (-1);
	if (ret == T_IND && get_ind(str, param_nb, ptrs[0]) != 1)
		return (-1);
	if (ret & T_LAB && get_lab(str, param_nb, ptrs[0], ptrs[1]) != 1)
		return (-1);
	if (ret == T_DIR && get_dir(str, param_nb, ptrs[0]) != 1)
		return (-1);
	return (1);
}

//example: st r1, 564545465456456546454564454354354435435435453735425452442725727 is ok! (tested asm 'zaz' and 'jino')
int				check_params(char **str, t_op *ref, t_ope *ope, t_asm *a)
{
	u_int		param_nb;

	param_nb = 0;
	if (ref->nb_param == 0)
		return (1);
	while (param_nb < ref->nb_param)
	{
		skip_whitespaces(str);
		if (check_param(str, param_nb, ref, (void *[2]){ope, a->syms}) != 1)
			return (-1);
		skip_whitespaces(str);
		param_nb++;
		if (param_nb == ref->nb_param)
			break ;
		if (**str != SEPARATOR_CHAR)
			return (-1);
		(*str)++;
	}
	return (1);
}
