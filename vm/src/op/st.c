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
	//if (e->cyc_since_beg > 8900 && e->cyc_since_beg < 9000)
		//printf("r%hhu = %d\n",e->map[mod_map(prc->pc + offset)], params[1]);
	offset += 1;
	if (((ocp >> 4) % 4) == IND_CODE)
	{
		params[2] = get_index(e, (ocp >> 4) % 4, prc, mod_map(prc->pc + offset));
		if (e->par.verb & V_4)
			printf("P %4d | st r%d %d\n", prc->id,
			e->map[mod_map(prc->pc + 2)], params[2]);
		//if (e->cyc_since_beg > 8900 && e->cyc_since_beg < 9000)
		//{
		//	printf("before");
		//	print_ADV(e, mod_map(prc->pc + params[2]), nb_bytes_to_skip(OP_ST, prc->pc));
		//}
		//copy_value(params[1], e, mod_map(prc->pc + params[2]));
		//if (e->cyc_since_beg > 8900 && e->cyc_since_beg < 9000)
		//{
		//	printf("after");
		//	print_ADV(e, mod_map(prc->pc + params[2]), nb_bytes_to_skip(OP_ST, prc->pc));
		//}
		copy_value(params[1], e, mod_map(prc->pc + (params[2] % IDX_MOD)));
    	return (0);
	}
	else if (((ocp >> 4) % 4) == REG_CODE)
	{
		params[2] = e->map[mod_map(prc->pc + offset)];
		prc->r[params[2]] = params[1];
	}
	if (e->par.verb & V_4)
	{
		printf("P %4d | st r%d %d\n", prc->id,
		e->map[mod_map(prc->pc + 2)], params[2]);
	}
	return (0);
}
