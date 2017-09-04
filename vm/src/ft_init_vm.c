#include "vm.h"

static void init_chp(t_chp *chp)
{
	chp->nb = 0;
	ft_bzero(chp->name, PROG_NAME_LENGTH + 1);
	ft_bzero(chp->comment, COMMENT_LENGTH + 1);
	chp->file_name = NULL;
}

static void init_champions(t_env *e)
{
	int i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		init_chp(&(e->par.champions[i]));
		i++;
	}
}

int			ft_init_vm(t_env *e)
{
	ft_bzero(e->map, MEM_SIZE);
	ft_bzero(e->map_color, MEM_SIZE);
	color_tab();						//init color tab for printf
	op_tab_init();						//init the operation table
	op_fun_tab_init();
	e->prc_lst = NULL;
	e->cyc = CYCLE_TO_DIE;
	e->cyc_counter = 0;
	e->nb_live = 0;
	e->nb_checks = 0;
	e->par.dump = 0;
	e->par.nb_cyc = 0;
	e->par.nb_chp = 0;
	e->par.verb = 0;
	e->par.print = 0;
	e->cyc_since_beg = 0;
	e->last_alive = 0;
	e->speed = 5;
	init_champions(e);
	return (1);
}
