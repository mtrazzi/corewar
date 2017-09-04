#include "vm.h"

# define OP_LDI 10

int     ldi(t_env *e, t_prc *prc)
{
	u_char	ocp;
	int		params[4]; //first parameter is params[1], nothing in params[0]
	int		offset;
	int		addr;

	offset = 1;	//at first offset is one byte after op_code
	ocp = e->map[(prc->pc + offset) % MEM_SIZE];
	offset += 1;
	if (((ocp >> 6) % 4) == DIR_CODE)
		params[1] = get_index(e, (ocp >> 6) % 4, prc, prc->pc + offset);
	if (((ocp >> 6) % 4) == IND_CODE)
		params[1] = get_value(e, (ocp >> 6) % 4, prc, prc->pc + offset);
	while (params[1] < 0)	//problem with negative in modulo
		params[1] += IDX_MOD;
	offset += sizeof_param(OP_LDI, (ocp >> 6) % 4);
	params[2] = get_index(e, (ocp >> 4) % 4, prc, prc->pc + offset);
	while (params[2] < 0)	//problem with negative in modulo
		params[2] += IDX_MOD;
	offset += sizeof_param(OP_LDI, (ocp >> 4) % 4);
	addr = (prc->pc + (params[1] + params[2]) % IDX_MOD) % MEM_SIZE;
	prc->r[e->map[(prc->pc + offset) % MEM_SIZE]] = get_value(e, IND_CODE, prc, addr);
	if (e->par.verb & V_4)
	{
		ft_printf("P    %d | ldi %d %d r%d\n", prc->id, params[1], params[2],
		e->map[(prc->pc + offset) % MEM_SIZE]);
		ft_printf("       | -> load from %d + %d = %d (with pc and mod %d)\n", \
		params[1], params[2], params[1] + params[2], addr);
	}
    return (0);
}
