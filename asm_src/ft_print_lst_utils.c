#include "asm.h"

int		ft_print_elt_str(char *str)
{
	ft_printf("%s\n", str);
	return (1);
}

void	ft_print_lst_str(t_dll *lst)
{
	dll_foreach(lst, &ft_print_elt_str);
}
