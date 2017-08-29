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
	while (++i < MAX_OP)
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


u_int		get_type(char *str)
{
	if (*str == '\0')
		return (NOT_A_PARAM_CODE);
	if (*str == DIRECT_CHAR && *(str + 1) == LABEL_CHAR)
		return (T_LAB);
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

int		check_param(char *str, int param_nb, t_op *ref, t_ope *ope)
{
	u_int ret;
	u_int res;

	if (!*str)
		return (-1);//
	if ((ret = check_type(str, param_nb, ref)) & (32 | 16))
		return (ret);
	//get le reste du param
	return (1);
}


//example: st r1, 564545465456456546454564454354354435435435453735425452442725727 is ok! (tested asm 'zaz' and 'jino')
int	check_params(char *str, t_op *ref)
{
	t_ope	ope;
	int		param_nb;

	skip_whitespaces(&str);
	return (1);
}
