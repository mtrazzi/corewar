#include "asm.h"
 
int main(int ac, char **av)
{
	t_asm *e;
	
	e = ft_init_asm();
	ft_printf("maman je suis en vie!!!!!\n\n\n\n\nn\n");
	if (ac != 2)
		return (ft_error_asm(e, "not the valid number of arguments. Expected one."));
	if (ft_file_to_lst_asm(e, av[1]) < 0)
		return (-1);
	if (ft_update_fd_asm(e, av[1]) < 0)
		return (ft_error_asm(e, "error opening file."));
	ft_free_asm_env(e);
	return (0);
}
