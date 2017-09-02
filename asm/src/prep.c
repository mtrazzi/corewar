
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
	while (syms)//iter?
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
	dll_foreach_content(ops, nb_bytes_op);
	dll_foreach(ops, calc_add_size);
	return (1);
}

int		rsbv(t_dll *dll, void *data)
{
	t_dll	*dlltmp;
	t_dll	*syms;
	int	i;
	t_ope	*ope;

	dlltmp = NULL;
	syms = data;
	ope = (t_ope *)dll->content;
	i = -1;
	// ft_printf("{green}[%u] %u{eoc}\n", ope->op_code, ope->nb_param);
	while (++i < ope->nb_param)//MAX_ARGS_NUMBER
	{
		if (ope->type_param[i] & T_LAB)
		{
			// ft_printf("{red}TEST2 _%d_{eoc}\n", i + 1);
			dlltmp = dll_iter_dll(syms, get_sym_by_sym, (void *)(long)ope->params[i]);
			// ft_printf("{red}TEST2.1 %p{eoc}\n", ((t_sym *)dlltmp->content)->corresponding_ope);
			if (dlltmp != NULL && ((t_sym *)dlltmp->content)->corresponding_ope)//should not append
				ope->params[i] = ((t_sym *)dlltmp->content)->corresponding_ope->address_in_size - ope->address_in_size;
			else if (dlltmp != NULL)
				ope->params[i] = ((t_ope *)get_last(dll)->content)->address_in_size + ((t_ope *)get_last(dll)->content)->size + 1 - ope->address_in_size;//not
			// ft_printf("{red}TEST2.2{eoc}\n");
			dlltmp = NULL;
		}
	}
	return (1);
}


int		replace_sym_by_value(t_dll *ops, t_dll *syms)
{
	dll_iter_int(ops, rsbv, syms);//new foreach taking a void!//protect against !syms
	return (1);
}

int		prep(t_asm *a)
{
	// if (!a->syms || !a->ops)
	// 	return (-1);
	associate_ope_to_label(a->syms, a->ops);
	calc_sizes(a->ops);
	replace_sym_by_value(a->ops, a->syms);//replace by iter
	a->header.prog_size = ((t_ope *)get_last(a->ops)->content)->address_in_size + ((t_ope *)get_last(a->ops)->content)->size;
	return (1);
}
