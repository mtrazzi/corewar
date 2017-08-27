#include "asm.h"

t_arg_type	ft_give_type(char *param)
{
	if (*param == 'r')
		return (REG_CODE);
	else if (*param == '%')
		return (DIR_CODE);
	else
		return (IND_CODE);
}

t_arg_type	ft_give_pcb(t_ope op)
{	
	return (op.p1.type << 6 | op.p2.type << 4 | op.p3.type << 2); 
}
