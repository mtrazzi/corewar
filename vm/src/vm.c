#include "vm.h"

# define DEBUG_MAIN 1

int main(int ac, char **av)
{
	t_env	e;

	ft_init_vm(&e);
	if (parse_arg_vm(ac, av, &e) < 0)
		return (ft_free_vm_env(&e));
	if (parse_all_files(&e) < 0)
		return (ft_free_vm_env(&e));
	if (init_all_processes(&e) < 0)
		return (ft_free_vm_env(&e));
	if (DEBUG_MAIN)
		print_map(e);
	ft_free_vm_env(&e);
	return (0);
}
