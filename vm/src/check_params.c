#include "vm.h"

# define DEBUG_CHECK_PARAMS 0

static 	int	is_reg(t_env *e, int pos)
{
	int reg_nb;

	reg_nb = e->map[mod_map(pos)];
	if (!(reg_nb > 0 && reg_nb < REG_NUMBER + 1) && DEBUG_CHECK_PARAMS)
		ft_printf("reg_nb is %d\npos is %d\n", reg_nb, pos);
	return (reg_nb > 0 && reg_nb < REG_NUMBER + 1);
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
	return (g_op_tab[op_code - 1].nb_param >= sum);
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
	//dont check nb_par -> tested in param_corr
}

static int		are_param_correct2(t_env *e, t_prc *prc, u_char ocp, u_int op_code)
{
	u_int	tmp;
	u_int	max;
	u_int	i;
	int		offset;

	max = g_op_tab[op_code - 1].nb_param + 1;
	i = 1;
	offset = 1;
	while (i < max)
	{
		tmp = (ocp >> (4 - i) * 2) & LAST_TWO_BITS;
		if (!g_op_tab[op_code - 1].type_param[i - 1] & (tmp == IND_CODE ? T_IND : tmp))
			return (0);
		if (tmp == T_REG && !is_reg(e, prc->pc + offset))
			return (0);
		offset += sizeof_param(op_code, tmp == IND_CODE ? T_IND : tmp);
		i++;
	}
	return (1);
}

