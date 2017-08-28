#include "asm.h"

void	ft_write_param(int fd, int label, t_param p)
{
	if (p.type == DIR_CODE)
		ft_write_be(fd, p.n, label);
	else if (p.type == IND_CODE)
		ft_write_be(fd, p.n, PAR_SIZE_IND);
	else if (p.type == REG_CODE)
		ft_write_be(fd, p.n, PAR_SIZE_REG);
}

void	ft_write_op(int fd, t_ope op)
{
	int label;

	label = give_label(op.op_code);
	ft_write_be(fd, op.op_code, 1);
	ft_write_be(fd, ft_give_pcb(op), 1); 
	ft_write_param(fd, label, op.p1);
	ft_write_param(fd, label, op.p2);
	ft_write_param(fd, label, op.p3);
}
