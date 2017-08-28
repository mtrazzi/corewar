#include "vm.h"

int		ft_error_vm(t_env *e, char *error_message)
{
	ft_free_vm_env(e);
	ft_fprintf(2, "Error: %s\n", error_message);
	return (-1);
}

int		ft_perror_vm(t_env *e)
{
	ft_free_vm_env(e);
	perror("Error");
	return (-1);
}
