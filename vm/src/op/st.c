#include "vm.h"

# define OP_ST 3

int     st(t_env *e, t_prc *prc)
{
	u_char	ocp;
	int		params[4]; //first parameter is params[1], nothing in params[0]
	int		offset;

	offset = 1;	//at first offset is one byte after op_code
	ocp = e->map[mod_map(prc->pc + offset)];
	offset += 1;
	params[1] = prc->r[e->map[mod_map(prc->pc + offset)]];
	offset += 1;
	if (((ocp >> 4) % 4) == IND_CODE)
	{
		params[2] = get_index(e, (ocp >> 4) % 4, prc, mod_map(prc->pc + offset));
		if (e->par.verb & V_4)
			ft_printf("P%5d | st r%d %d\n", prc->id,
			e->map[mod_map(prc->pc + 2)], params[2]);
		copy_value(params[1], e, mod_map(prc->pc + params[2]));
    return (0);
	}
	else if (((ocp >> 4) % 4) == REG_CODE)
	{
		params[2] = e->map[mod_map(prc->pc + offset)];
		prc->r[params[2]] = params[1];
	}
	if (e->par.verb & V_4)
		ft_printf("P%5d | st r%d %d\n", prc->id,
		e->map[mod_map(prc->pc + 2)], params[2]);
    return (0);
}
