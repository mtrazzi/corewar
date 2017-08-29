#include "vm.h"

int		ft_error_vm(int err_nb, char *error_message)
{
	ft_fprintf(2, "Error: %s\n", error_message);
	return (err_nb);
}

int		ft_perror_vm(int err_nb)
{
	perror("Error");
	return (err_nb);
}
