#include "vm.h"

# define DEBUG_MAIN 0

int main(int ac, char **av)
{
	t_env	e;

	ft_init_vm(&e);
	if (parse_arg_vm(ac, av, &e) < 0)
		return (ft_free_vm_env(&e));
	if (parse_all_files(&e) < 0)
		return (ft_free_vm_env(&e));
	if (DEBUG_MAIN)
		print_env(e);
	if (!e.par.print)
		print_introduction(&e);
	if (init_all_processes(&e) < 0)
		return (ft_free_vm_env(&e));
	if (run_vm(&e) < 0)
		return (ft_free_vm_env(&e));
	if (!e.par.print)
		print_conclusion(&e);
	ft_free_vm_env(&e);
	return (0);
}
