#include "asm.h"

void	write_param(int fd, int label, t_param p)
{
	if (p.type == DIR_CODE)
		write_be(fd, p.n, label);
	else if (p.type == IND_CODE)
		write_be(fd, p.n, PAR_SIZE_IND);
	else if (p.type == REG_CODE)
		write_be(fd, p.n, PAR_SIZE_REG);
}

void	write_op(int fd, t_ope *ope)
{
	int	i;

	write_be(fd, ope->op_code, 1);
	write_be(fd, ope->ocp, 1); 
	i = -1;
	while (++i < MAX_ARGS_NUMBER)
	{
		if (ope->type_param[i] & T_REG)
			write_be(fd, ope->params[i], PAR_SIZE_REG);
		else if (ope->type_param[i] & T_IND)
			write_be(fd, ope->params[i], PAR_SIZE_IND);
		else if (ope->type_param[i] & T_DIR)
			write_be(fd, ope->params[i], 4 - 2 * ope->op_tab_x->label_size);
	}
}

/*
void	write_param(int fd, int label, t_param p)
{
	if (p.type == DIR_CODE)
		write_be(fd, p.n, label);
	else if (p.type == IND_CODE)
		write_be(fd, p.n, PAR_SIZE_IND);
	else if (p.type == REG_CODE)
		write_be(fd, p.n, PAR_SIZE_REG);
}

void	write_op(int fd, t_ope *ope)
{
	int label;

	label = give_label(op.op_code);
	write_be(fd, op.op_code, 1);
	write_be(fd, ft_give_pcb(op), 1); 
	write_param(fd, label, op.p1);
	write_param(fd, label, op.p2);
	write_param(fd, label, op.p3);
}
*/