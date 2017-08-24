#include "asm.h"
 
int main(int ac, char **av)
{
	t_asm *e;
	
	e = ft_init_asm();
	if (ac != 2)
		return (ft_error_asm(e, "not the valid number of arguments. Expected one."));
	ft_file_to_lst_asm(e, av[1]);
	ft_print_lst_str(e->lst);
	ft_free_asm_env(e);
	return (0);
}
