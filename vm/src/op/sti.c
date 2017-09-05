#include "vm.h"

# define OP_STI 11
# define DEBUG_STI 1

int     sti(t_env *e, t_prc *prc)
{
	u_char	ocp;
	int		params[4]; //first parameter is params[1], nothing in params[0]
	int		offset;
	int		addr;

	offset = 1;	//at first offset is one byte after op_code
	ocp = e->map[mod_map(prc->pc + offset)];
	offset += 1;
	params[1] = prc->r[e->map[mod_map(prc->pc + offset)]]; //first param is a register
	offset += 1;
	params[2] = get_index(e, (ocp >> 4) % 4, prc, prc->pc + offset);
	while (params[2] < 0)	//problem with negative in modulo
		params[2] += IDX_MOD;
	offset += sizeof_param(OP_STI, (ocp >> 4) % 4);
	params[3] = get_index(e, (ocp >> 2) % 4, prc, prc->pc + offset);
	while (params[3] < 0)	//problem with negative in modulo
		params[3] += IDX_MOD;
	offset += sizeof_param(OP_STI, (ocp >> 4) % 4);
	addr = mod_map(prc->pc + (params[2] + params[3]) % IDX_MOD);
	copy_value(params[1], e, addr);
	if (e->par.verb & V_4)
	{
		ft_printf("P    %d | sti r%d %d %d\n", prc->id, e->map[mod_map(prc->pc + 2)], \
		params[2], params[3]);
		ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n", \
		params[2], params[3], params[2] + params[3], addr);
	}
    return (0);
}
