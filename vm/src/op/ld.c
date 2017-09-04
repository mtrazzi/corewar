#include "vm.h"

# define OP_LD 2

int     ld(t_env *e, t_prc *prc)
{
	u_char	ocp;
	int		params[4]; //first parameter is params[1], nothing in params[0]
	int		offset;
	int		reg_nb;

	offset = 1;	//at first offset is one byte after op_code
	ocp = e->map[(prc->pc + offset) % MEM_SIZE];
	offset += 1;
	params[1] = get_value(e, (ocp >> 6) % 4, prc, (prc->pc + offset) % MEM_SIZE);
	offset += sizeof_param(OP_LD, (ocp >> 6) % 4);
	reg_nb = e->map[(prc->pc + offset) % MEM_SIZE];	//second param is a register
	prc->r[reg_nb] = params[1];
	prc->carry = prc->r[reg_nb] == 0; //carry is 1 if result of op is 0
	if (e->par.verb & V_4)
		ft_printf("P    %d | ld %d r%d\n", prc->id, params[1], reg_nb);
    return (0);
}
