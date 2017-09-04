#include "vm.h"

# define OP_ST 3

int     st(t_env *e, t_prc *prc)
{
	u_char	ocp;
	int		params[4]; //first parameter is params[1], nothing in params[0]
	int		offset;

	offset = 1;	//at first offset is one byte after op_code
	ocp = e->map[(prc->pc + offset) % MEM_SIZE];
	offset += 1;
	params[1] = prc->r[e->map[(prc->pc + offset) % MEM_SIZE]];
	offset += 1;
	if (((ocp >> 4) % 4) == IND_CODE)
	{
		params[2] = get_index(e, (ocp >> 4) % 4, prc, (prc->pc + offset) % MEM_SIZE);
		while (params[2] < 0)
			params[2] += IDX_MOD; //problem with negative with modulo
		copy_value(params[1], e, params[2] % MEM_SIZE);
	}
	else if (((ocp >> 4) % 4) == REG_CODE)
	{
		params[2] = e->map[(prc->pc + offset) % MEM_SIZE];
		prc->r[params[2]] = params[1];
	}
	prc->carry = (params[1] == 0); //carry is 1 if result of op is 0
	if (e->par.verb)
		ft_printf("P    %d | st r%d %d\n", prc->id,
		e->map[(prc->pc + 2) % MEM_SIZE], params[2]);
    return (0);
}
