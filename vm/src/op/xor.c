#include "vm.h"

# define OP_XOR 8

int     xor(t_env *e, t_prc *prc) //p1 ^ p2 -> p3 with p3 register
{
	u_char	ocp;
	int		params[4]; //first parameter is params[1], nothing in params[0]
	int		offset;
	int		reg_nb;

	offset = 1;	//at first offset is one byte after op_code
	ocp = e->map[(prc->pc + offset) % MEM_SIZE];
	offset += 1;
	params[1] = get_value(e, (ocp >> 6) % 4, prc, (prc->pc + offset) % MEM_SIZE);
	offset += sizeof_param(OP_XOR, (ocp >> 6) % 4);
	params[2] = get_value(e, (ocp >> 4) % 4, prc, (prc->pc + offset) % MEM_SIZE);
	offset += sizeof_param(OP_XOR, (ocp >> 4) % 4);
	reg_nb = e->map[(prc->pc + offset) % MEM_SIZE];	//third param is a register
	prc->r[reg_nb] = params[1] ^ params[2];
	prc->carry = prc->r[reg_nb] == 0; //carry is 1 if result of op is 0
	if (e->par.verb & V_4)
		ft_printf("P    %d | xor %d %d r%d\n", prc->id, params[1], params[2], reg_nb);
    return (0);
}
