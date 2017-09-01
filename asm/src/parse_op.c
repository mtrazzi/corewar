#include "asm.h"

u_int		get_type(char *str)
{
	if (*str == '\0')
		return (NOT_A_PARAM_CODE);
	if (*str == DIRECT_CHAR && *(str + 1) == LABEL_CHAR)
		return (T_LAB | T_DIR);//T_LAB
	if (*str == LABEL_CHAR)
		return (T_LAB | T_IND);
	if (*str == DIRECT_CHAR)
		return (T_DIR);//return (DIR_CODE);
	if (*str == REG_CHAR)
		return (T_REG);//return (REG_CODE);
	if (*str == '-' || ft_isdigit(*str))
		return (T_IND);//return (IND_CODE);
	return (NOT_A_PARAM_CODE);
}

//check_type
u_int		check_type(char *str, int param_nb, t_op *ref)
{
	u_int type;

	type = get_type(str);
	if (type == NOT_A_PARAM_CODE)
		return (16);//NOT_A_PARAM_CODE);//16
	if ((ref->type_param[param_nb] & type) == 0)
		return (32);//BAD_OP_PARAM);//32
	return (type);
}

int		check_param(char **str, int param_nb, t_op *ref, t_ope *ope, t_dll *syms)
{
	u_int ret;

	ft_printf("{blue}check_param: [%s]{eoc}\n", *str);
	if ((ret = check_type(*str, param_nb, ref)) & (32 | 16))
		return (ret);
	ope->type_param[param_nb] = ret;
	ft_printf("{Iblue}\tret %u{eoc}\n", ret);
	//get le reste du param
	if (ret == T_REG)
	{
		if (get_reg(str, param_nb, ope) != 1)
			return (-1);
	}
	else if (ret == T_IND)
	{
		if (get_ind(str, param_nb, ope) != 1)
			return (-1);
	}
	else if (ret & T_LAB)//ret == T_LAB | T_DIR || ret == T_LAB | T_DIR//or mettre en dernier
	{
		if (get_lab(str, param_nb, ope, syms) != 1)
			return (-1);
	}
	else if (ret == T_DIR)
	{
		if (get_dir(str, param_nb, ope) != 1)
			return (-1);
	}
	ft_printf("{blue}DONE{eoc}\n");
	return (1);
}

//example: st r1, 564545465456456546454564454354354435435435453735425452442725727 is ok! (tested asm 'zaz' and 'jino')
int	check_params(char **str, t_op *ref, t_ope *ope, t_asm *a)
{
	int		param_nb;

	param_nb = 0;
	if (ref->nb_param == 0)
		return (1);
	ft_printf("{yellow}check_params: [%s]{eoc}\n", *str);
	while (param_nb < ref->nb_param)
	{
		skip_whitespaces(str);
		if (check_param(str, param_nb, ref, ope, a->syms) != 1)
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
