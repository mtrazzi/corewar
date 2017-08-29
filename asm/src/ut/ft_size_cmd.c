#include "asm.h"

u_int		convert_op_code(u_int op_code)
{
	u_int	result;

	result = 1;
	while (op_code > 1)
	{
		result *= 2;
		op_code--;
	}
	return (result);
}

int			give_label(u_int op_code)
{
	u_int	code;

	code = convert_op_code(op_code);
	return (((IS_LABEL_2 & code) > 0) * LABEL_2 +\
			((IS_LABEL_4 & code) > 0) * LABEL_4);
}

static	int	count_types(t_ope op, t_arg_type type)
{
	int		sum;

	sum = 0;
	sum += (op.p1.type == type);
	sum += (op.p2.type == type);
	sum += (op.p3.type == type);
	return (sum);
}

int			nb_bytes_op(t_ope op)
{
	int		sum;
	int		label;
	u_int	pcb;

	sum = 0;
	label = give_label(op.op_code);	
	pcb = ft_give_pcb(op);
	sum += count_types(op, DIR_CODE) * label;
	sum += count_types(op, IND_CODE) * PAR_SIZE_IND;
	sum += count_types(op, REG_CODE) * PAR_SIZE_REG;
	sum += ((IS_PCB & convert_op_code(op.op_code)) > 0); // sum += g_op_tab[op].OCP
	return (sum + 1);
}
