#include "vm.h"

static 	int	is_reg(t_env *e, int pos)
{
	int reg_nb;

	reg_nb = e->map[mod_map(pos)];
	return (reg_nb > 0 && reg_nb < REG_NUMBER);
}

static u_int	convert_to_mask(u_int type_of_param)
{
    if (type_of_param == REG_CODE)
        return (T_REG);
    else if (type_of_param == IND_CODE)
        return (T_IND);
    else if (type_of_param == DIR_CODE)
        return (T_DIR);
    return (0);
}

static int is_nb_par_correct(u_int op_code, u_char ocp)
{
	u_int sum;

	sum = 0;
	while (ocp > 0)
	{
		sum += (ocp % 4);
		ocp /= 4;
	}
	return (g_op_tab[op_code - 1].nb_param == sum);
}

int		is_ocp_correct(u_char ocp, int op_code)
{
	u_int	mask;
	int		par_nb;

	par_nb = MAX_ARGS_NUMBER; //== 4
	while (ocp > 0)
	{
		mask = convert_to_mask(ocp % 4);
		if (!(g_op_tab[op_code - 1].type_param[par_nb - 1] & mask))
			return (0);
		ocp = ocp / 4;
		par_nb -=1;
	}
	return (1);
}


int		check_params(t_env *e, t_prc *prc, int op_code)
{
	u_char	ocp;
	u_int	offset;

	if (!(g_op_tab[op_code - 1].ocp))
		return (1);
	ocp = e->map[mod_map(prc->pc + 1)];
	if (!(is_nb_par_correct(ocp, op_code) && is_ocp_correct(ocp, op_code)))
		return (0);
	offset = 2; //opcode and ocp skipped
	while (ocp > 0)
	{
		if ((ocp % 4) == REG_CODE && !is_reg(e, prc->pc + offset))
			return (0);
		offset += sizeof_param(op_code, ocp % 4);
		ocp /= 4;
	}
	return (1);
}
