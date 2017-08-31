#include "asm.h"

#define NAME_DIFFERENT 0
#define NAME_EQUAL 1

//build a fonction to type_param[nb_param:] = 0
t_op    g_op_tab[MAX_OP] =
{
/*
**  {"nom", 	nb_param,	{type des param}, 										opcode, nb_cycles,	"nom_complet", 		OCP 
*/
    {"live", 	1,			{T_DIR}, 												1, 		10, 		"alive", 			0, 0},
    {"ld", 		2, 			{T_DIR | T_IND, T_REG}, 								2, 		5,	 		"load", 			1, 0},
    {"st", 		2, 			{T_REG, T_IND | T_REG}, 								3, 		5, 			"store", 			1, 0},
    {"add", 	3, 			{T_REG, T_REG, T_REG}, 									4, 		10, 		"addition", 		1, 0},
    {"sub", 	3, 			{T_REG, T_REG, T_REG}, 									5, 		10, 		"soustraction", 	1, 0},
    {"and", 	3, 			{T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 	6, 		6,			"et",				1, 0},
    {"or", 		3, 			{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 	7, 		6,			"ou", 				1, 0},
    {"xor", 	3, 			{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 	8, 		6,			"ou", 				1, 0},
    {"zjmp", 	1, 			{T_DIR}, 												9, 		20, 		"jump if zero", 	0, 1},
    {"ldi", 	3, 			{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 			10,		25,			"load index", 		1, 1},
    {"sti", 	3, 			{T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 			11,		25,			"store index", 		1, 1},
    {"fork", 	1, 			{T_DIR}, 												12,		800, 		"fork", 			0, 1},
    {"lld", 	2, 			{T_DIR | T_IND, T_REG}, 								13, 	10, 		"long load", 		1, 0},
    {"lldi", 	3, 			{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},			14,		50,			"long load index",	1, 1},
    {"lfork", 	1, 			{T_DIR}, 												15,		1000, 		"long fork", 		0, 1},
    {"aff", 	1, 			{T_REG}, 												16,		2, 			"aff", 				1, 0},
    {0, 		0, 			{0}, 													0, 		0, 			0, 					0, 0}
};



int		compare_op_names(char *str, int len, char *op_name)
{
	if (ft_strlen(op_name) != len)
		return (NAME_DIFFERENT);
	if (ft_strncmp(op_name, str, len) == 0)
		return (NAME_EQUAL);
	return (NAME_DIFFERENT);
}

t_op	*does_op_exist_in_op_tab(char *str, int len)
{
	int		i;

	i = -1;
	while (++i < MAX_OP - 1)
	{
		if (compare_op_names(str, len, g_op_tab[i].name) == NAME_EQUAL)
			return (&g_op_tab[i]);
	}
	return (NULL);
}

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

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
	while (**str && ft_strchr(LABEL_CHARS, **str))
		(*str)++;
	if (tmp == *str)
		return (-1);
	sym_tmp = does_label_exist_in_sym_dll(tmp, *str - tmp, syms);
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

u_int		get_type(char *str)
{
	if (*str == '\0')
		return (NOT_A_PARAM_CODE);
	if (*str == DIRECT_CHAR && *(str + 1) == LABEL_CHAR)
		return (T_LAB);//T_LAB | T_DIR
	//if (*str == LABEL_CHAR)
	//	return (T_LAB | T_DIR)
	if (*str == DIRECT_CHAR)
		return (T_DIR);//return (DIR_CODE);
	if (*str == REG_CHAR)
		return (T_REG);//return (REG_CODE);
	if (*str == '-' || ft_isdigit(*str))
		return (T_IND);//return (IND_CODE);
	return (NOT_A_PARAM_CODE);
}

# define BAD_OP_PARAM -21
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
	u_int res;

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
	else if (ret == T_LAB)//ret == T_LAB | T_DIR || ret == T_LAB | T_DIR//or mettre en dernier
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

t_ope	*create_ope_from_ope_and_ref(t_ope *ope, t_op *ref)
{
	t_ope	*new;

	if ((new = create_ope()) == NULL)
		return (NULL);
	new->nb_param = ref->nb_param;
	ft_memcpy(new->type_param, ope->type_param, sizeof(u_int) * MAX_ARGS_NUMBER);
	ft_memcpy(new->params, ope->params, sizeof(u_int) * MAX_ARGS_NUMBER);
	new->op_code = ref->op_code;
	new->size = 0;
	new->address_in_size = 0;
	new->op_tab_x = ope->op_tab_x;
	new->line_nb = ope->line_nb;
	return (new);
}

t_dll	*create_ope_dll(t_ope *ope, t_op *ref)
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
