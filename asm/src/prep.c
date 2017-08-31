
#include "asm.h"

int	cmp_line_nb_label_line(t_dll *e, void *data)
{
	if (((t_ope *)e->content)->line_nb >= (u_int)*((long *)data))
		return (0);
	return (1);
}

int		associate_ope_to_label(t_dll *syms, t_dll *ops)
{
	long	tmp;
	t_dll	*ope;

	if (!syms || !ops)
		return (1);
	while (syms)
	{
		tmp = ((t_sym *)syms->content)->line_number_parsing_help;
		ope = dll_iter_dll(ops, cmp_line_nb_label_line, &tmp);
		if (ope != NULL)
		{
			((t_sym *)syms->content)->corresponding_ope = (t_ope *)ope->content;
		}
		else
			((t_sym *)syms->content)->corresponding_ope = NULL;//(t_ope *)ops->content;
		syms = syms->next;
	}
	return (1);
}


int		calc_sizes(t_dll *ops)
{
	return (1);
}


int		prep(t_asm *a)
{
	// if (!a->syms || !a->ops)
	// 	return (-1);
	associate_ope_to_label(a->syms, a->ops);
	return (1);
}