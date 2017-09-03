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

int		get_ind(char **str, int param_nb, t_ope *ope)//MOD_QQCHOSE
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

int		get_lab(char **str, int param_nb, t_ope *ope, t_dll *syms)//int type
{
	char	*tmp;
	t_sym	*sym_tmp;

	// *str += 2;
	//*str += type & T_DIR ? 2: 10;
	if (**str == DIRECT_CHAR)
		(*str)++;
	if (**str == LABEL_CHAR)
		(*str)++;
	tmp = *str;
	while (**str && ft_strchr(LABEL_CHARS, **str))//change to moving tmp ;)
	 	(*str)++;
	// while (*tmp && ft_strchr(LABEL_CHARS, *tmp))
	// 	tmp++;
	if (tmp == *str)
		return (-1);
	sym_tmp = does_label_exist_in_sym_dll(tmp, *str - tmp, syms);
	// sym_tmp = does_label_exist_in_sym_dll(*str, tmp - *str, syms);
	if (sym_tmp == NULL)
		return (-1);
	ope->params[param_nb] = sym_tmp->sym;
	return (1);
}

int		get_dir(char **str, int param_nb, t_ope *ope)//IDX_MOD
{
	u_int	res;
	char	*tmp;

	//ft_printf("{Bgreen}\t%s{eoc}\n", *str);
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