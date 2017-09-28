/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_op2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 16:27:37 by pkirsch           #+#    #+#             */
/*   Updated: 2017/09/28 18:49:36 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		get_reg(char **str, int param_nb, t_ope *ope)
{
	u_int	res;
	char	*tmp;

	(*str)++;
	tmp = *str;
	while (**str && ft_isdigit(**str))
		(*str)++;
	if (tmp - *str == 0)
		return (-1);
	res = (u_int)ft_atoi_mod(tmp);
	if (res == 0 || res > REG_NUMBER)
		return (-1);
	ope->params[param_nb] = res;
	return (1);
}

int		get_ind(char **str, int param_nb, t_ope *ope)
{
	u_int	res;
	char	*tmp;

	tmp = *str;
	if (**str == '-')
		(*str)++;
	while (**str && ft_isdigit(**str))
		(*str)++;
	if ((*tmp == '-' && tmp - *str == 1) || tmp - *str == 0)
		return (-1);
	res = (u_int)ft_atoi_mod(tmp);
	ope->params[param_nb] = (u_short)res;
	return (1);
}

int		get_lab(char **str, int param_nb, t_ope *ope, t_dll *syms)
{
	char	*tmp;
	t_sym	*sym_tmp;

	if (**str == DIRECT_CHAR)
		(*str)++;
	if (**str == LABEL_CHAR)
		(*str)++;
	tmp = *str;
	while (*tmp && ft_strchr(LABEL_CHARS, *tmp))
		tmp++;
	if (tmp == *str)
		return (-1);
	sym_tmp = does_label_exist_in_sym_dll(*str, tmp - *str, syms);
	if (sym_tmp == NULL)
		return (-1);
	*str = tmp;
	ope->params[param_nb] = sym_tmp->sym;
	return (1);
}

int		get_dir(char **str, int param_nb, t_ope *ope)
{
	u_int	res;
	char	*tmp;

	(*str)++;
	tmp = *str;
	if (**str == '-')
		(*str)++;
	while (**str && ft_isdigit(**str))
		(*str)++;
	if ((*tmp == '-' && tmp - *str == 1) || tmp - *str == 0)
		return (-1);
	res = (u_int)ft_atoi_mod(tmp);
	ope->params[param_nb] = res;
	return (1);
}
