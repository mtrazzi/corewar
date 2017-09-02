
#include "asm.h"

// ft_printf("dll: %14p\tnext: %14p\tprev:%14p\t\t", lst,
// 						lst->next, lst->prev);


//add to dllst lib
void	dll_str_(t_dll *dll)
{
	if (dll)
		ft_printf("dll: %14p\tnext: %14p\tprev:%14p\n",
					dll, dll->next, dll->prev);
	else
		ft_printf("null\n");
}

void	dll_print(char *msg, t_dll *lst)
{
	ft_printf("%8c\n", '-');
	msg ? ft_printf(msg) : 0;
	if (!lst)
		ft_printf("%11c\t%s\n", ' ', "empty");
	while (lst)
	{
		dll_str_(lst);
		lst = lst->next;
	}
	ft_printf("%8c\n", '-');
}

void	sym_str_(t_sym *sym)
{
	if (sym)
		ft_printf("sym {%s} {%u} {%u} {%p}\n",
				sym->label, sym->sym, sym->line_number_parsing_help, sym->corresponding_ope);
	else
		ft_printf("null\n");
}

void	sym_dll_print(char *msg, t_dll *lst)
{
	ft_printf("%8c\n", '-');
	msg ? ft_printf(msg) : 0;
	if (!lst)
		ft_printf("%11c\t%s\n", ' ', "empty");
	while (lst)
	{
		sym_str_(lst->content);
		lst = lst->next;
	}
	ft_printf("%8c\n", '-');
}

int	ope_tabs_str_(t_ope *ope)
{
	int	i;

	i = -1;
	while (++i < MAX_ARGS_NUMBER)
		ft_printf("\t%u %d\n", ope->type_param[i], ope->params[i]);
	return (1);
}

int	op_tab_str_(t_op *op)
{
	int	i;

	i = -1;
	while (++i < MAX_ARGS_NUMBER)
		ft_printf("\t%u\n", op->type_param[i]);
	return (1);
}

void	op_str_(t_op *op)
{
	if (op)
	{
		ft_printf("{%s} _%u_ op_code[%u] cycles{%u} {%s} ocp:%u +%u+\n", op->name, op->nb_param, op->op_code,
					op->nb_cycles, op->full_name, op->ocp, op->label_size);
		op_tab_str_(op);
	}
	else
		ft_printf("null\n");
}


void	ope_str_(t_ope *ope)
{
	if (ope)
	{
		ft_printf("{red}");
		ft_printf("nb_param:%u op_code[%u] size{%u} add{%u} _%p_ line:%u ocp[%#hhx %hhb]\n", ope->nb_param, ope->op_code,
					ope->size, ope->address_in_size, ope->op_tab_x, ope->line_nb, ope->ocp, ope->ocp);
		ope_tabs_str_(ope);
		ft_printf("{eoc}");
		op_str_(ope->op_tab_x);
	}
	else
		ft_printf("null\n");
}

//void	dll_print_f(msg, lst, f)-> IN DLLST
//type def la fonction?
void	dll_print_f(char *msg, t_dll *lst, void f())//color?
{
	ft_printf("%8c\n", '-');
	msg ? ft_printf(msg) : 0;
	if (!lst)
		ft_printf("%11c\t%s\n", ' ', "empty");
	while (lst)//foreach?
	{
		ft_printf("dll: %14p\tnext: %14p\tprev:%14p\tcontent:%14p\t\t\n", lst,//remove \n!
 						lst->next, lst->prev, lst->content);
		f(lst->content);
		lst = lst->next;
	}
	ft_printf("%8c\n", '-');
}