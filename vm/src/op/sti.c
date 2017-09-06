#include "vm.h"

# define OP_STI 11
# define DEBUG_STI 1

int     sti(t_env *e, t_prc *prc)
{
	u_char	ocp;
	int		params[4]; //first parameter is params[1], nothing in params[0]
	int		offset;
	int		addr;
	u_char tmp;


	offset = 1;	//at first offset is one byte after op_code
	ocp = e->map[mod_map(prc->pc + offset)];
	offset += 1;
	tmp = e->map[mod_map(prc->pc + offset)];
	if (tmp <= 0 || tmp > REG_NUMBER)
		return (-1);
	params[1] = prc->r[tmp]; //first param is a register
	ft_printf("{blue}cest la{eoc}\n");
	offset += 1;
	params[2] = get_index(e, (ocp >> 4) % 4, prc, prc->pc + offset);
	offset += sizeof_param(OP_STI, (ocp >> 4) % 4);
	//ft_printf("type param%u", (ocp >> 4) % 4);
	params[3] = get_index(e, (ocp >> 2) % 4, prc, prc->pc + offset);
	offset += sizeof_param(OP_STI, (ocp >> 2) % 4);//ocp >> 2 ?
	addr = prc->pc + (params[2] + params[3]) % IDX_MOD;
	if (e->par.verb & V_4)
	{
		ft_printf("P%5d | sti r%d %d %d\n", prc->id, e->map[mod_map(prc->pc + 2)], \
		params[2], params[3]);
		ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n", \
		params[2], params[3], params[2] + params[3], addr);
	}
	copy_value(params[1], e, mod_map(addr));
    return (0);
}

// 0b0000 0000