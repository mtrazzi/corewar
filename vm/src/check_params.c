#include "vm.h"

# define DEBUG_CHECK_PARAMS 0

static 	int	is_reg(t_env *e, int pos)
{
	int reg_nb;

	reg_nb = e->map[mod_map(pos)];
	if (!(reg_nb > 0 && reg_nb <= REG_NUMBER) && DEBUG_CHECK_PARAMS)
		ft_printf("reg_nb is %d\npos is %d\n", reg_nb, pos);
	return (reg_nb > 0 && reg_nb <= REG_NUMBER);
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

static int is_nb_par_correct(u_char ocp, u_int op_code)
{
	u_int sum;

	sum = 0;
	while (ocp > 0)
	{
		sum += (ocp & LAST_TWO_BITS) > 0;
		ocp = ocp >> 2;
	}
	if (g_op_tab[op_code - 1].nb_param != sum && DEBUG_CHECK_PARAMS)
	{
		ft_printf("nb parameters incorrect : %d but expected %d\n",
		sum, g_op_tab[op_code - 1].nb_param);
	}
	return (g_op_tab[op_code - 1].nb_param <= sum);
}

static int		are_param_correct(t_env *e, t_prc *prc, u_char ocp, int op_code)
{
	u_int	mask;
	int		par_nb;
	u_int	offset;

	par_nb = g_op_tab[op_code - 1].nb_param;
	ocp = (ocp >> (MAX_ARGS_NUMBER - par_nb) * 2);
	offset = nb_bytes_to_skip(op_code, ocp); //from end to beginning
	while (ocp > 0)
	{
		mask = convert_to_mask(ocp & LAST_TWO_BITS);
		if (!(g_op_tab[op_code - 1].type_param[par_nb - 1] & mask))
			return (0);
		offset -= sizeof_param(op_code, ocp & LAST_TWO_BITS);
		if (mask == T_REG && !is_reg(e, prc->pc + offset))
			return (0);
		ocp = ocp >> 2;
		par_nb -=1;
	}
	return (1);
}

int		check_params(t_env *e, t_prc *prc, int op_code)
{
	u_char	ocp;

	if (!(g_op_tab[op_code - 1].ocp))
		return (1);
	ocp = e->map[mod_map(prc->pc + 1)];
	return (is_nb_par_correct(ocp, op_code) && are_param_correct(e, prc, ocp, op_code));
}
