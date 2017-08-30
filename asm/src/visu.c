
#include "asm.h"

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
				sym->label, sym->sym, sym->line_number_parsing_help, sym->first_ope);
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
