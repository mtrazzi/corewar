#include "asm.h"


int		init_g_op(void)
{

	//build a fonction to type_param[nb_param:] = 0
	//g_op_tab =
	//{
	/*
	**  {"nom", 	nb_param,	{type des param}, 										opcode, nb_cycles,	"nom_complet", 		OCP 
	*/
	g_op_tab[0] = (t_op){"live", 	1,			{T_DIR}, 												1, 		10, 		"alive", 			0, 0};
	g_op_tab[1] = (t_op){"ld", 		2, 			{T_DIR | T_IND, T_REG}, 								2, 		5,	 		"load", 			1, 0};
	g_op_tab[2] = (t_op){"st", 		2, 			{T_REG, T_IND | T_REG}, 								3, 		5, 			"store", 			1, 0};
	g_op_tab[3] = (t_op){"add", 	3, 			{T_REG, T_REG, T_REG}, 									4, 		10, 		"addition", 		1, 0};
	g_op_tab[4] = (t_op){"sub", 	3, 			{T_REG, T_REG, T_REG}, 									5, 		10, 		"soustraction", 	1, 0};
	g_op_tab[5] = (t_op){"and", 	3, 			{T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 	6, 		6,			"et",				1, 0};
	g_op_tab[6] = (t_op){"or", 		3, 			{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 	7, 		6,			"ou", 				1, 0};
	g_op_tab[7] = (t_op){"xor", 	3, 			{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 	8, 		6,			"ou", 				1, 0};
	g_op_tab[8] = (t_op){"zjmp", 	1, 			{T_DIR}, 												9, 		20, 		"jump if zero", 	0, 1};
	g_op_tab[9] = (t_op){"ldi", 	3, 			{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 			10,		25,			"load index", 		1, 1};
	g_op_tab[10] = (t_op){"sti", 	3, 			{T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 			11,		25,			"store index", 		1, 1};
	g_op_tab[11] = (t_op){"fork", 	1, 			{T_DIR}, 												12,		800, 		"fork", 			0, 1};
	g_op_tab[12] = (t_op){"lld", 	2, 			{T_DIR | T_IND, T_REG}, 								13, 	10, 		"long load", 		1, 0};
	g_op_tab[13] = (t_op){"lldi", 	3, 			{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},			14,		50,			"long load index",	1, 1};
	g_op_tab[14] = (t_op){"lfork", 	1, 			{T_DIR}, 												15,		1000, 		"long fork", 		0, 1};
	g_op_tab[15] = (t_op){"aff", 	1, 			{T_REG}, 												16,		2, 			"aff", 				1, 0};
	g_op_tab[16] = (t_op){0, 		0, 			{0}, 													0, 		0, 			0, 					0, 0};
	//};
	return (1);
}

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
