#include "vm.h"

# define OP_ZJMP 0x09

u_char	read_op_code(u_char *map, u_int	index)
{
 	return (map[index]);
}

int		process_exec_op_update_cyc_left(t_env *e, t_prc *prc)
{
	int skip;
	prc->cyc_left -= 1;
	if (prc->cyc_left == 0 && prc->op_code != NB_OP + 1)
	{
		g_op_fun_tab[prc->op_code - 1](e, prc);
		if (prc->op_code != OP_ZJMP || !(prc->carry))
		{
			skip = nb_bytes_to_skip(prc->op_code, e->map[(prc->pc + 1) % MEM_SIZE]);
			if (e->par.verb)
				print_ADV(e, prc->pc, skip);
			prc->pc = (prc->pc + nb_bytes_to_skip(prc->op_code, skip)) % MEM_SIZE;
		}
	}
	else if (prc->cyc_left == 0)
		prc->pc = (prc->pc + 1) % MEM_SIZE;
	return (0);
}

int		process_load_op(t_env *e, t_prc *prc)
{
	if (prc->cyc_left != 0)
		return (0);
	prc->op_code = read_op_code(e->map, prc->pc);
	if (prc->op_code == 0 || prc->op_code > 16)//
		prc->op_code = NB_OP + 1;
	prc->cyc_left = g_op_tab[prc->op_code - 1].nb_cycles;
	prc->newly_created = 0;
	return (0);
}

int		do_process(t_env *e, t_prc *prc)
{
	if (prc->cyc_left == 0)
	{
		if (prc->op_code != NB_OP + 1)
			g_op_fun_tab[prc->op_code - 1](e, prc);
		if (prc->op_code != NB_OP + 1 &&
				(prc->op_code != OP_ZJMP || !(prc->carry)))
			prc->pc = (prc->pc + nb_bytes_to_skip(prc->op_code,
						e->map[(prc->pc + 1) % MEM_SIZE])) % MEM_SIZE;
		prc->op_code = read_op_code(e->map, prc->pc);
		if (prc->op_code == 0 || prc->op_code > 16)//NB_VALID_OP
		{
			prc->op_code = NB_OP + 1;
			prc->pc = (prc->pc + 1) % MEM_SIZE;
		}
		prc->cyc_left = g_op_tab[prc->op_code - 1].nb_cycles;
	}
	prc->cyc_left -= 1;
	return (0);
}

/*
int		do_process(t_env *e, t_prc *prc)
{
	u_char  op_code;

	op_code = e->map[prc->pc];
	if (!op_code || op_code > 16)                       //op_code not valid
	{
		prc->pc = (prc->pc + 1) % MEM_SIZE;
		return (0);
	}
	if (prc->cyc_left == 0)                             //cursor just moved on byte
		prc->cyc_left = g_op_tab[op_code - 1].nb_cycles;
	else
		prc->cyc_left -= 1;
	if (prc->cyc_left == 0)                             //all cycles have passed
	{
		g_op_fun_tab[op_code - 1](e, prc);
		if (op_code != OP_ZJMP || !(prc->carry))        //do not do this if zjmp and carry == 1
			prc->pc = (prc->pc + nb_bytes_to_skip(op_code,
						e->map[(prc->pc + 1) % MEM_SIZE])) % MEM_SIZE;
	}
	return (0);
}
*/


/*
if (prc->cyc_left == 0)
	{
		if (prc->op_code != NB_OP + 1)
			g_op_fun_tab[prc->op_code - 1](e, prc);
		if (prc->op_code != NB_OP + 1 &&
				(prc->op_code != OP_ZJMP || !(prc->carry)))
			prc->pc = (prc->pc + nb_bytes_to_skip(prc->op_code,
						e->map[(prc->pc + 1) % MEM_SIZE])) % MEM_SIZE;
		prc->op_code = read_op_code(e->map, prc->pc);
		if (prc->op_code == 0 || prc->op_code > 16)//NB_VALID_OP
		{
			prc->op_code = NB_OP + 1;
			prc->pc = (prc->pc + 1) % MEM_SIZE;
		}
		prc->cyc_left = g_op_tab[prc->op_code - 1].nb_cycles;
	}
	prc->cyc_left -= 1;
	return (0);
*/
