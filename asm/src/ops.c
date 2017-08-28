#include "asm.h"

#define NAME_DIFFERENT 0
#define NAME_EQUAL 1

//build a fonction to type_param[nb_param:] = 0
t_op    g_op_tab[17] =
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

void	skip_whitespaces(char **str)
{
	if (!str || !*str)
		return ;
	while (**str && ft_is_withespace(**str))
		(*str)++;
}

void	skip_to_whitespaces(char **str)//or end
{
	if (!str || !*str)
		return ;
	while (**str && !ft_is_withespace(**str))
		(*str)++;
}

char	*get_next_separator(char *str)//or end
{
	if (!str)
		return (NULL);
	while (*str && *str != SEPARATOR_CHAR)
		str++;
	return (str);
}

char	*get_next_whitespace(char *str)//or end
{
	if (!str)
		return (NULL);
	while (*str && !ft_is_withespace(*str))
		str++;
	return (str);
}

//check_type
int		check_type(char *str, int param_nb, t_op *ref)
{
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