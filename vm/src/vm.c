#include "vm.h"

int main(int ac, char **av)
{
	t_env	e;

	ft_init_vm(&e);
	if (parse_arg_vm(ac, av, &e) < 0)
		return (ERR_PARSING);
	ft_free_vm_env(&e);
	return (0);
}
